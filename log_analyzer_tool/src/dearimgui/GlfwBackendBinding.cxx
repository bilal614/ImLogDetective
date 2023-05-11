
#include "dearimgui/GlfwBackendBinding.h"

#include "dearimgui/ITextWidgetFactory.h"
#include "dearimgui/IWindowFactory.h"
#include "LogAnalyzerToolDefs.h"
#include "MainView.h"
#include "MainViewModel.h"
#include "dearimgui/IOContext.h"
#include "dearimgui/MainViewPort.h"
#include "dearimgui/WindowFactory.h"
#include "dearimgui/TextWidgetFactory.h"
#include <iostream>
#include <string>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>


namespace LogAnalyzerTool
{

void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

struct GlfwBackendBinding::Impl
{
    Impl();
    ~Impl();
    std::string glShaderLanguageVersion;
    GLFWwindow* window;
    std::unique_ptr<IMainViewPort> mainViewPort;
    std::unique_ptr<IOContext> ioContext;
    std::unique_ptr<IWindowFactory> windowFactory;
    std::unique_ptr<ITextWidgetFactory> textWidgetFactory;
    std::unique_ptr<MainViewModel> mainViewModel;
    std::unique_ptr<MainView> mainView;
};

GlfwBackendBinding::Impl::~Impl()
{
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

GlfwBackendBinding::Impl::Impl() :
    glShaderLanguageVersion{"#version 130"},
    windowFactory{},
    mainViewModel{std::make_unique<MainViewModel>()},
    mainView{ }
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
    {
        std::cout << "glfwInit failed" << std::endl;
    }

    // GL 3.3 + GLSL 130
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    auto screenWidth = glfwGetVideoMode(primaryMonitor)->width;
    auto screenHeight = glfwGetVideoMode(primaryMonitor)->height;
    // Create window with graphics context
    window = glfwCreateWindow(screenWidth, screenHeight, LogAnalyzerToolApplicationName.c_str(), NULL, NULL);
    if (window != NULL)
    {
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1); // Enable vsync

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Setup Dear ImGui style
        //ImGui::StyleColorsDark();
        ImGui::StyleColorsClassic();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glShaderLanguageVersion.c_str());
    }
    ioContext = std::make_unique<IOContext>();
    ioContext->unsetIniFile();
    mainViewPort = std::make_unique<MainViewPort>();
    textWidgetFactory = std::make_unique<TextWidgetFactory>();
    windowFactory  = std::make_unique<WindowFactory>(*mainViewPort);
    mainView = std::make_unique<MainView>(*windowFactory.get(), *textWidgetFactory.get(), *mainViewModel.get());

}

GlfwBackendBinding::GlfwBackendBinding() : p{std::make_unique<Impl>()}
{

}

GlfwBackendBinding::~GlfwBackendBinding() = default;

void GlfwBackendBinding::runMainLoop()
{
    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    while (!glfwWindowShouldClose(p->window))
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        p->mainView->show();

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(p->window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(p->window);
    }
}

}