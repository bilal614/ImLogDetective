#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "PtyMaster.h"
#include <fstream>
#include <future>
#include <poll.h>

namespace TestLogFetchingTool
{

TEST(TestPtyMaster, test_PtyMaster_with_tr) {

    LogScpWrapper::ProcessStartInfo process_start_info {
        .executable_path{"tr"},
        .arguments{"tr", "a-z", "A-Z"},
    };
    
    std::unique_ptr<LogScpWrapper::IPtyMaster> process{std::make_unique<LogScpWrapper::PtyMaster>(process_start_info)};

    process->start();

    auto& piped_child = process->getChild();

    char rd_buf[1024] = {0}, wr_buf[1024] = {0};
    ssize_t bytes_read = 0;

    memset(wr_buf, 0, 1024);
    strcpy(wr_buf, "Hello World!\n");
    std::cout << wr_buf << std::endl;
    write(piped_child.master_fd, wr_buf, strlen(wr_buf));

    sleep(1);
    memset(rd_buf, 0, 1024);
    bytes_read = read(piped_child.master_fd, rd_buf, 1024);
    std::cout << "bytes_read=" << bytes_read << ", " << rd_buf << std::endl;

    sleep(1);
    memset(wr_buf, 0, 1024);
    strcpy(wr_buf, "Welcome...asdskajshdkjashd\n");
    std::cout << wr_buf << std::endl;
    write(piped_child.master_fd, wr_buf, strlen(wr_buf));

    memset(wr_buf, 0, 1024);
    strcpy(wr_buf, "Good Bye!\n");
    std::cout << wr_buf << std::endl;
    write(piped_child.master_fd, wr_buf, strlen(wr_buf));

    sleep(1);
    memset(rd_buf, 0, 1024);
    bytes_read = read(piped_child.master_fd, rd_buf, 1024);
    std::cout << "bytes_read=" << bytes_read << ", " << rd_buf << std::endl;

    piped_child.closeMasterChild();

    //process->kill();
}


TEST(TestPtyMaster, test_PtyMaster_with_sh) {

    LogScpWrapper::ProcessStartInfo process_start_info {
        .executable_path{"sh"},
        .arguments{"sh"},
    };

    std::unique_ptr<LogScpWrapper::IPtyMaster> process{std::make_unique<LogScpWrapper::PtyMaster>(process_start_info)};

    process->start();

    auto& piped_child = process->getChild();

    char rd_buf[1024] = {0}, wr_buf[1024] = {0};
    ssize_t bytes_read = 0;

    memset(wr_buf, 0, 1024);
    strcpy(wr_buf, "echo Hello World!\n");
    std::cout << wr_buf << std::endl;
    write(piped_child.master_fd, wr_buf, strlen(wr_buf));

    sleep(1);
    memset(rd_buf, 0, 1024);
    bytes_read = read(piped_child.master_fd, rd_buf, 1024);
    std::cout << "bytes_read=" << bytes_read << ", " << rd_buf << std::endl;

    sleep(1);
    memset(wr_buf, 0, 1024);
    strcpy(wr_buf, "echo Good Bye!\n");
    std::cout << wr_buf << std::endl;
    write(piped_child.master_fd, wr_buf, strlen(wr_buf));

    sleep(1);
    memset(rd_buf, 0, 1024);
    bytes_read = read(piped_child.master_fd, rd_buf, 1024);
    std::cout << "bytes_read=" << bytes_read << ", " << rd_buf << std::endl;

    piped_child.closeMasterChild();
    //process->kill();
}


}