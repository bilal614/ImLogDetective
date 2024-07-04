
#ifndef IMLOGDETECTIVE_DEARIMGUI_GLFWBACKENDBINDING_H
#define IMLOGDETECTIVE_DEARIMGUI_GLFWBACKENDBINDING_H

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

#endif