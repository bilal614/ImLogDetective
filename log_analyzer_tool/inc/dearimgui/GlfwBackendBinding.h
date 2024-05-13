#pragma once
#include <memory>

namespace ImLogDetective
{

class GlfwBackendBinding
{
public:
    GlfwBackendBinding();
    ~GlfwBackendBinding();
    void runMainLoop();
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}