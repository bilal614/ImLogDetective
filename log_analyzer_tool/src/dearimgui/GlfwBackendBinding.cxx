
#include "dearimgui/GlfwBackendBinding.h"
#include "dearimgui/IOContext.h"
#include "dearimgui/MainViewPort.h"
#include "dearimgui/ModalPopup.h"
#include "dearimgui/WidgetFactory.h"
#include "dearimgui/ImGuiTextFilterWrapper.h"
#include "dearimgui/TabBar.h"
#include "dearimgui/ITextWidgetFactory.h"
#include "dearimgui/IWindowFactory.h"
#include "dearimgui/ITabBar.h"
#include "event_handling/EventLoop.h"
#include "event_handling/Event.hpp"
#include "LogAnalyzerToolDefs.h"
#include "models/GzipFile.h"
#include "models/LogFileParser.h"
#include "presenters/FileListPresenter.h"
#include "presenters/LogFilePresenter.h"
#include "presenters/LogDataModelFactory.h"
#include "presenters/LogFileTabsPresenter.h"
#include "presenters/MainPresenter.h"
#include "views/FileListView.h"
#include "views/SelectionMenuBar.h"
#include "views/FolderSelectionPopup.h"
#include "views/LogView.h"
#include "views/LogFilterView.h"
#include <iostream>
#include <memory>
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
    std::unique_ptr<IIOContext> ioContext;
    std::unique_ptr<IEventLoop> eventLoop;
    std::unique_ptr<IWidgetFactory> widgetFactory;
    std::unique_ptr<IImGuiTextFilterWrapper> textFilterWrapper;
    std::unique_ptr<IModalPopup> modalPopup;
    std::unique_ptr<ISelectionMenuBar> selectionMenuBar;
    std::unique_ptr<IFolderSelectionPopup> folderSelectionPopup;
    std::unique_ptr<IFileListView> fileListView;
    std::unique_ptr<ILogFilterView> logFilterView;
    std::unique_ptr<ILogView> logView;
    std::unique_ptr<GzipFile> gzipFile;
    std::unique_ptr<ILogFileParser> logFileParser;
    std::unique_ptr<IFileListPresenter> fileListPresenter;
    std::unique_ptr<ILogFilePresenter> logFilePresenter;
    std::unique_ptr<ILogFileTabsPresenter> logFileTabsPresenter;
    std::unique_ptr<ILogDataModelFactory> logDataModelFactory;
    std::unique_ptr<ITabBar> tabBar;
    std::unique_ptr<MainPresenter> mainPresenter;
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
    widgetFactory{},
    logView{ nullptr },
    mainPresenter{ nullptr }
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
    window = glfwCreateWindow(screenWidth, screenHeight, WindowDefs::LogAnalyzerToolApplicationName, NULL, NULL);
    if (window != NULL)
    {
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1); // Enable vsync

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();
        //ImGui::StyleColorsLight();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glShaderLanguageVersion.c_str());
    }
    ioContext = std::make_unique<IOContext>();
    ioContext->unsetIniFile();
    mainViewPort = std::make_unique<MainViewPort>(*ioContext);
    widgetFactory  = std::make_unique<WidgetFactory>(*mainViewPort);
    eventLoop = std::make_unique<EventLoop>();
    selectionMenuBar = std::make_unique<SelectionMenuBar>();
    modalPopup = std::make_unique<ModalPopup>();
    folderSelectionPopup = std::make_unique<FolderSelectionPopup>(*modalPopup);
    textFilterWrapper = std::make_unique<ImGuiTextFilterWrapper>("Filter", -100);
    logFilterView = std::make_unique<LogFilterView>(*textFilterWrapper);
    tabBar = std::make_unique<TabBar>("LogFileTabs");
    logView = std::make_unique<LogView>(dynamic_cast<ITextWidgetFactory&>(*widgetFactory));
    fileListView = std::make_unique<FileListView>(dynamic_cast<IListTreeFactory&>(*widgetFactory));
    gzipFile = std::make_unique<GzipFile>();
    logFileParser = std::make_unique<LogFileParser>(*gzipFile);
    logFilePresenter = std::make_unique<LogFilePresenter>(
        dynamic_cast<IWindowFactory&>(*widgetFactory), 
        *eventLoop, 
        *logFilterView, 
        *logView,
        *logFileParser,
        *textFilterWrapper);
    logDataModelFactory = std::make_unique<LogDataModelFactory>();
    logFileTabsPresenter = std::make_unique<LogFileTabsPresenter>(*logFilePresenter, *logDataModelFactory, *tabBar, std::make_unique<Event<const std::string&>>());
    fileListPresenter = std::make_unique<FileListPresenter>(*logFileTabsPresenter, *fileListView);
    mainPresenter = std::make_unique<MainPresenter>(dynamic_cast<IWindowFactory&>(*widgetFactory),
        *mainViewPort,
        *selectionMenuBar,
        *folderSelectionPopup,
        *logFileTabsPresenter,
        *fileListPresenter);

}

GlfwBackendBinding::GlfwBackendBinding() : p{std::make_unique<Impl>()}
{
    p->eventLoop->start();
}

GlfwBackendBinding::~GlfwBackendBinding()
{
    p->eventLoop->stop();
}

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

        p->mainPresenter->update();

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