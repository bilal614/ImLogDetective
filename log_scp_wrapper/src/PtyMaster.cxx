#include "PtyMaster.h"

#include <functional>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/un.h>

namespace LogScpWrapper
{

constexpr const char* sock_path {"/tmp/us_btb"};
constexpr int buff_size = 2048;

void onChildExit(int signum)
{
    std::cout << "Child process exiting" << std::endl;
}

struct PtyMaster::Impl
{

    Impl(const ProcessStartInfo& processStartInfo);
    ~Impl() = default;

    std::vector<char*> getArguments();
    std::string getCommand();
    int ptyFork(pty_child& childinfo);

    ProcessStartInfo startInfo;
    pty_child forked_child;

    std::string name;
    int masterpt, slavept;

    char buff[buff_size];

};

PtyMaster::Impl::Impl(const ProcessStartInfo& processStartInfo) :
    startInfo{processStartInfo}
{
}

std::vector<char*> PtyMaster::Impl::getArguments()
{
    std::vector<char*> arguments;
    arguments.reserve(startInfo.arguments.size() + 1);

    //arguments.push_back(const_cast<char*>(startInfo.executable_path.filename().c_str()));
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

    std::cout << "ptsname=" << name << std::endl;
    p = fork();
    if(p < 0) return p; /* Fork failed */
    if(p == 0)  /* child, has pid of 0 */
    {
        signal(SIGINT, onChildExit);
        // Detach us from the current TTY
        setsid();
        close( masterpt );
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

        close( slavept );
        exit(0);
    }

    // We are the parent
    slavept=open(name.c_str(), O_RDWR|O_NOCTTY );

    childinfo.child_pid = p;
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
    p->ptyFork(p->forked_child);
    //Test

}

void PtyMaster::waitForExit()
{

}

bool PtyMaster::kill()
{
    //::kill(p->forked_child.child_pid ,SIGINT);
    return false;
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

}