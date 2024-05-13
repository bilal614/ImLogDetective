#include "dearimgui/GlfwBackendBinding.h"

int main(int, char**)
{
    ImLogDetective::GlfwBackendBinding glfwBinding;
    glfwBinding.runMainLoop();
    return 0;
}