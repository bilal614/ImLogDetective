#pragma once
#include <libssh2.h>
#include <iostream>

namespace LogFetchingTool
{
    
class LibSsh2Init 
{
public:
    static LibSsh2Init& getInstance()
    {
        static LibSsh2Init inst;
        return inst;
    }

    LibSsh2Init(const LibSsh2Init&) = delete;
    LibSsh2Init& operator=(const LibSsh2Init&) = delete;

private:
    LibSsh2Init()
    {
        if(libssh2_init(0) != 0)
        {
            std::cout << "LibSsh2Init:: Could not init libssh2 lib" << std::endl;
        } else {
            std::cout << "LibSsh2Init:: Init libssh2 lib succeeded" << std::endl;
        }
    }
    ~LibSsh2Init()
    {
        libssh2_exit();
    }
};

}