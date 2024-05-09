#include "log_scp_wrapper/PtyMaster.h"
#include <algorithm>
#include <iostream>
#include <fcntl.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <sys/un.h>
#include <sys/wait.h>

namespace {
    constexpr size_t RW_MAX_BUFF = 4096;
    constexpr size_t DEFAULT_AWAIT_SECONDS = 20;
    char NEW_LINE = '\n';
}

namespace LogScpWrapper
{

void onChildExit(int signum)
{
    std::cout << "Child process exiting..." << std::endl;
}

struct PtyMaster::Impl
{
    Impl(const ProcessStartInfo& processStartInfo);
    ~Impl();

    std::vector<char*> getArguments();
    std::string getCommand();
    int ptyFork(pty_child& childinfo);

    ProcessStartInfo startInfo;
    pty_child forked_child;

    std::string name;
    int masterpt, slavept;
    char rd_buf[RW_MAX_BUFF];
    char wr_buf[RW_MAX_BUFF];

    //Pty IO
    bool awaitDataOnFd();
    std::string sanitizeNewLineCharacters(const std::string& input);
    fd_set rfds;
    struct timeval tv;
};

PtyMaster::Impl::Impl(const ProcessStartInfo& processStartInfo) :
    startInfo{processStartInfo},
    wr_buf{0},
    rd_buf{0},
    tv{.tv_sec=DEFAULT_AWAIT_SECONDS, .tv_usec=0}
{
}

PtyMaster::Impl::~Impl()
{
    close(masterpt);
    close(slavept);
}

std::vector<char*> PtyMaster::Impl::getArguments()
{
    std::vector<char*> arguments;
    arguments.reserve(startInfo.arguments.size() + 1);

    for(const auto& arg : startInfo.arguments)
    {
        arguments.push_back(const_cast<char*>(arg.data()));
    }
    arguments.push_back(nullptr);
    return arguments;
}

std::string PtyMaster::Impl::getCommand()
{
    std::string command{startInfo.executable_path.c_str()};

    for(const auto& arg : startInfo.arguments)
    {
        command += std::string{" " +  arg};
    }
    return command;
}

std::string PtyMaster::Impl::sanitizeNewLineCharacters(const std::string& input)
{
    std::string output{input};
    output.erase(std::remove(output.begin(), output.end(), '\r'), output.end());
    output.erase(std::remove(output.begin(), output.end(), '\n'), output.end());
    return output;
}

bool PtyMaster::Impl::awaitDataOnFd()
{
    int retval = select(forked_child.master_fd + 1, &rfds, NULL, NULL, &tv);
    if (retval >= 1)
    {
        return true;
    }
    if(retval == 0)
    {
        std::cerr << "TIMEOUT EXPIRED" << std::endl;
    }
    if(retval < 0)
    {
        perror("select() failed");
    }
    return false;
}

int PtyMaster::Impl::ptyFork(pty_child& childinfo) {
    pid_t p;

    // Create a pseudo terminal for our process
    masterpt = posix_openpt(O_RDWR);

    if( masterpt == -1 ) 
    {
        return -1;
    }

    fcntl(masterpt, F_SETFL, O_NONBLOCK);

    if( grantpt( masterpt )!=0 ) 
    {
        return -1;
    }

    if( unlockpt( masterpt )!=0 )
    {
        return -1;
    }

    name = ptsname(masterpt);
    struct winsize size;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &size) >= 0)
    {
        ioctl(masterpt, TIOCSWINSZ, &size);
    }

    p = fork();
    if(p < 0) return p; /* Fork failed */
    if(p == 0)  /* child, has pid of 0 */
    {
        signal(SIGINT, onChildExit);
        // Detach us from the current TTY
        setsid();
        close(masterpt);
        // This line makes the ptty our controlling tty. We do not otherwise need it open
        slavept=open(name.c_str(), O_RDWR );

        ioctl(slavept, TIOCSWINSZ, &size);
        setbuf(stdout, NULL);
        dup2(slavept, STDIN_FILENO);
        dup2(slavept, STDOUT_FILENO);

        auto arguments = getArguments();
        if(execvp(startInfo.executable_path.c_str(), &arguments[0]) == -1)
        {
            std::cout << strerror(errno) << ", execvp failed" << std::endl;
        }

        close(slavept);
        exit(0);
    }

    // We are the parent
    slavept=open(name.c_str(), O_RDWR|O_NOCTTY );

    childinfo.pid = p;
    childinfo.master_fd = masterpt;

    return 0;
}

PtyMaster::PtyMaster(const ProcessStartInfo& processStartInfo) : 
    p{std::make_unique<Impl>(processStartInfo)}
{
}

PtyMaster::~PtyMaster() = default;

void PtyMaster::start()
{
    FD_ZERO(&p->rfds);
    p->ptyFork(p->forked_child);
    FD_SET(p->forked_child.master_fd, &p->rfds);
}

void PtyMaster::waitForExit()
{
}

bool PtyMaster::kill()
{
    if(::kill(p->forked_child.pid ,SIGINT) == -1)
    {
        std::cerr << strerror(errno) << std::endl;
        return false;
    }
    return true;
}

std::filesystem::path PtyMaster::getCurrentWorkingDirectory()
{
    return std::filesystem::path();
}

uint32_t PtyMaster::getPid()
{
    return getpid();
}

std::string PtyMaster::getUser()
{
    return std::string{};
}

pty_child& PtyMaster::getChild()
{
    return p->forked_child;
}

void PtyMaster::writeLine(const std::string& input)
{
    auto lastInputChar = *(--input.end());
    bool inputEndsWithNewLineCharacter = lastInputChar == NEW_LINE;
    memset(p->wr_buf, 0, RW_MAX_BUFF);
    std::string line{input};
    if(!inputEndsWithNewLineCharacter && input.size() <= RW_MAX_BUFF)
    {
        line += NEW_LINE;
    }
    strcpy(p->wr_buf, line.c_str());
    ::write(p->forked_child.master_fd, p->wr_buf, strlen(p->wr_buf));
}

std::pair<bool, std::string> PtyMaster::read(size_t bytesToRead)
{
    if (p->awaitDataOnFd())
    {
        memset(p->rd_buf, 0, RW_MAX_BUFF);
        auto bytes_read = ::read(p->forked_child.master_fd, p->rd_buf, bytesToRead);
        return {true, p->sanitizeNewLineCharacters(p->rd_buf)};
    }
    return {false, std::string{}};
}

std::pair<bool, std::string> PtyMaster::read()
{
    return read(RW_MAX_BUFF);
}

}