
#include "dearimgui/GlfwBackendBinding.h"
#include "dearimgui/IOContext.h"
#include "dearimgui/MainViewPort.h"
#include "views/WidgetFactory.h"
#include "dearimgui/ImGuiMenuBarWrapper.h"
#include "dearimgui/ImGuiTextFilterWrapper.h"
#include "dearimgui/ImGuiWidgetWrapper.h"
#include "dearimgui/TabBar.h"
#include "views/ITextWidgetFactory.h"
#include "views/IWindowFactory.h"
#include "dearimgui/ITabBar.h"
#include "EventHandling/EventLoop.h"
#include "EventHandling/Event.hpp"
#include "ImLogDetectiveDefs.h"
#include "ScpWrapper/AuthenticationWorkFlow.h"
#include "ScpWrapper/ScpExecutor.h"
#include "models/AssetsConfigurator.h"
#include "models/GzipFile.h"
#include "models/LogFileParser.h"
#include "models/Mini.h"
#include "presenters/CopyLogsPresenter.h"
#include "presenters/FileListPresenter.h"
#include "presenters/LogFilePresenter.h"
#include "presenters/LogDataModelFactory.h"
#include "presenters/LogFileTabsPresenter.h"
#include "presenters/MainPresenter.h"
#include "views/FileListView.h"
#include "views/SelectionMenuBar.h"
#include "views/FolderSelectionPopup.h"
#include "views/CopyLogsPopup.h"
#include "views/ProtectedInputPopup.h"
#include "views/LogView.h"
#include "views/LogFilterView.h"
#include <iostream>
#include <memory>
#include <string>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <GLFW/glfw3.h>


namespace ImLogDetective
{

void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

struct GlfwBackendBinding::Impl
{
    Impl();
    ~Impl();

    void applyColorTheme();

    std::string glShaderLanguageVersion;
    GLFWwindow* window;
    std::unique_ptr<IMainViewPort> mainViewPort;
    std::unique_ptr<AssetsConfigurator> assetsConfigurator;
    std::unique_ptr<IIOContext> ioContext;
    std::unique_ptr<LogEventHandling::IEventLoop> eventLoop;
    std::unique_ptr<IImGuiWidgetWrapper> imGuiWidgetWrapper;
    std::unique_ptr<IWidgetFactory> widgetFactory;
    std::unique_ptr<IImGuiTextFilterWrapper> textFilterWrapper;
    std::unique_ptr<IImGuiMenuBarWrapper> imGuiMenuBarWrapper;
    std::unique_ptr<ISelectionMenuBar> selectionMenuBar;
    std::unique_ptr<IFolderSelectionPopup> folderSelectionPopup;
    std::unique_ptr<ICopyLogsPopup> copyLogsPopup;
    std::unique_ptr<IProtectedInputPopup> protectedInputPopup;
    std::unique_ptr<IFileListView> fileListView;
    std::unique_ptr<ILogFilterView> logFilterView;
    std::unique_ptr<ILogView> logView;
    std::unique_ptr<GzipFile> gzipFile;
    std::unique_ptr<IMini> mini;
    std::unique_ptr<ILogFileParser> logFileParser;
    std::unique_ptr<ICopyLogsPresenter> copyLogsPresenter;
    std::unique_ptr<IFileListPresenter> fileListPresenter;
    std::unique_ptr<ILogFilePresenter> logFilePresenter;
    std::unique_ptr<ILogFileTabsPresenter> logFileTabsPresenter;
    std::unique_ptr<ILogDataModelFactory> logDataModelFactory;
    std::unique_ptr<ITabBar> tabBar;
    std::unique_ptr<MainPresenter> mainPresenter;
    std::unique_ptr<ImLogDetective::IScpExecutor> scpExecutor;
    ImLogDetective::AuthenticationWorkFlow authenticationWorkFlow;

    GLFWimage icon[1];

};

GlfwBackendBinding::Impl::~Impl()
{
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    stbi_image_free(icon[0].pixels);

    glfwDestroyWindow(window);
    glfwTerminate();
}

void GlfwBackendBinding::Impl::applyColorTheme()
{
    ImGui::StyleColorsDark();
    ImGuiStyle* style = &ImGui::GetStyle();
    ImVec4* colors = style->Colors;
    colors[ImGuiCol_Button]                 = ImVec4(0.16f, 0.19f, 0.12f, 0.40f);
    colors[ImGuiCol_ButtonHovered]          = ImVec4(0.16f, 0.19f, 0.12f, 1.00f);
    colors[ImGuiCol_ButtonActive]           = ImVec4(0.16f, 0.03f, 0.12f, 1.00f);
    
    colors[ImGuiCol_FrameBg]                = ImVec4(0.16f, 0.19f, 0.18f, 0.54f);
    colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.16f, 0.19f, 0.18f, 0.40f);
    colors[ImGuiCol_FrameBgActive]          = ImVec4(0.26f, 0.29f, 0.28f, 0.67f);

    colors[ImGuiCol_Header]                 = ImVec4(0.08f, 0.09f, 0.08f, 0.25f);
    colors[ImGuiCol_HeaderHovered]          = ImVec4(0.18f, 0.18f, 0.18f, 0.95f);
    colors[ImGuiCol_HeaderActive]           = ImVec4(0.18f, 0.18f, 0.18f, 0.95f);

    colors[ImGuiCol_Tab]                    = ImVec4(0.36f, 0.39f, 0.38f, 0.54f);
    colors[ImGuiCol_TabHovered]             = ImVec4(0.36f, 0.39f, 0.38f, 0.85f);
    colors[ImGuiCol_TabActive]              = ImVec4(0.56f, 0.59f, 0.58f, 0.54f);
    colors[ImGuiCol_TabUnfocused]           = ImVec4(0.36f, 0.39f, 0.38f, 0.54f);
    colors[ImGuiCol_TabUnfocusedActive]     = ImVec4(0.36f, 0.39f, 0.38f, 0.54f);
}

GlfwBackendBinding::Impl::Impl() :
    glShaderLanguageVersion{"#version 130"},
    widgetFactory{},
    logView{ nullptr },
    mainPresenter{ nullptr },
    assetsConfigurator{std::make_unique<AssetsConfigurator>()}
{
    icon[0].pixels = stbi_load(assetsConfigurator->getIconFile().c_str(), &icon[0].width, &icon[0].height, 0, 4);

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
    window = glfwCreateWindow(screenWidth, screenHeight, WindowDefs::ApplicationName, NULL, NULL);
    if (window != NULL)
    {
        glfwSetWindowIcon(window, 1, icon); 
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1); // Enable vsync

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        // Setup Dear ImGui style
        //ImGui::StyleColorsDark();
        applyColorTheme();

        // Setup Platform/Renderer backends
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init(glShaderLanguageVersion.c_str());
    }

    ioContext = std::make_unique<IOContext>();
    ioContext->unsetIniFile();
    ioContext->setFontFromTtfFile(assetsConfigurator->getDefaultTtfFile());
    mainViewPort = std::make_unique<MainViewPort>(*ioContext);
    imGuiWidgetWrapper = std::make_unique<ImGuiWidgetWrapper>();
    imGuiMenuBarWrapper = std::make_unique<ImGuiMenuBarWrapper>();
    widgetFactory  = std::make_unique<WidgetFactory>(*mainViewPort, *imGuiWidgetWrapper);
    eventLoop = std::make_unique<LogEventHandling::EventLoop>();
    scpExecutor = std::make_unique<ImLogDetective::ScpExecutor>(*eventLoop, authenticationWorkFlow);
    selectionMenuBar = std::make_unique<SelectionMenuBar>(*imGuiMenuBarWrapper);
    folderSelectionPopup = std::make_unique<FolderSelectionPopup>(dynamic_cast<IModalPopupFactory&>(*widgetFactory));
    copyLogsPopup = std::make_unique<CopyLogsPopup>(dynamic_cast<IModalPopupFactory&>(*widgetFactory));
    protectedInputPopup = std::make_unique<ProtectedInputPopup>(dynamic_cast<IModalPopupFactory&>(*widgetFactory));
    textFilterWrapper = std::make_unique<ImGuiTextFilterWrapper>("Filter", -100);
    logFilterView = std::make_unique<LogFilterView>(*textFilterWrapper, *imGuiWidgetWrapper);
    tabBar = std::make_unique<TabBar>("LogFileTabs");
    logView = std::make_unique<LogView>(dynamic_cast<ITextWidgetFactory&>(*widgetFactory));
    fileListView = std::make_unique<FileListView>(dynamic_cast<IListTreeFactory&>(*widgetFactory));
    gzipFile = std::make_unique<GzipFile>();
    mini = std::make_unique<Mini>(IniDefs::IniFile);
    logFileParser = std::make_unique<LogFileParser>(*gzipFile);
    copyLogsPresenter = std::make_unique<CopyLogsPresenter>(*copyLogsPopup, *protectedInputPopup, *scpExecutor, *mini);
    logFilePresenter = std::make_unique<LogFilePresenter>(
        dynamic_cast<IWindowFactory&>(*widgetFactory), 
        *eventLoop, 
        *logFilterView, 
        *logView,
        *logFileParser,
        *textFilterWrapper);
    logDataModelFactory = std::make_unique<LogDataModelFactory>();
    logFileTabsPresenter = std::make_unique<LogFileTabsPresenter>(*logFilePresenter, *logDataModelFactory, *tabBar, std::make_unique<LogEventHandling::Event<const std::string&>>());
    fileListPresenter = std::make_unique<FileListPresenter>(*logFileTabsPresenter, *fileListView);
    mainPresenter = std::make_unique<MainPresenter>(dynamic_cast<IWindowFactory&>(*widgetFactory),
        *mainViewPort,
        *selectionMenuBar,
        *folderSelectionPopup,
        *logFileTabsPresenter,
        *fileListPresenter,
        *copyLogsPresenter,
        *mini);
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