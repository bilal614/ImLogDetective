#include "dearimgui/GlfwBackendBinding.h"

int main(int, char**)
{
    LogAnalyzerTool::GlfwBackendBinding glfwBinding;
    glfwBinding.runMainLoop();
    return 0;
}