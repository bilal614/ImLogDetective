# CMake entry point
cmake_minimum_required (VERSION 3.11)
project(IMGUI_LOG_ANALYZER_TOOL C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_ROOT ${PROJECT_SOURCE_DIR})

find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(glfw3 3.3 REQUIRED)

pkg_check_modules(GLFW3 REQUIRED glfw3)

if(OPENGL_FOUND AND PKG_CONFIG_FOUND AND GLFW3_FOUND)

    include_directories(
        ${OPENGL_INCLUDE_DIRS}
        ${GLFW3_INCLUDE_DIRS}
    )

    add_library(imgui_glfw_opengl SHARED
        ${PROJECT_SOURCE_DIR}/imgui/imgui.cpp
        ${PROJECT_SOURCE_DIR}/imgui/imgui_demo.cpp
        ${PROJECT_SOURCE_DIR}/imgui/imgui_draw.cpp
        ${PROJECT_SOURCE_DIR}/imgui/imgui_tables.cpp
        ${PROJECT_SOURCE_DIR}/imgui/imgui_widgets.cpp
        ${PROJECT_SOURCE_DIR}/imgui/backends/imgui_impl_glfw.cpp
        ${PROJECT_SOURCE_DIR}/imgui/backends/imgui_impl_opengl3.cpp
        ${PROJECT_SOURCE_DIR}/imgui/misc/cpp/imgui_stdlib.cpp
    )

    target_include_directories(imgui_glfw_opengl PRIVATE 
        ${PROJECT_SOURCE_DIR}/imgui
    )
    
    SET(PROJECT_INCLUDE_DIRS 
        ${PROJECT_SOURCE_DIR}/imgui
        ${PROJECT_SOURCE_DIR}/imgui/backends
    )

    SET (PROJECT_LINK_LIBRARIES imgui_glfw_opengl
        ${OPENGL_LIBRARIES}
        ${GLFW3_LIBRARIES}
        ${CMAKE_DL_LIBS} #link to dl lib for dynamic loading
        -lX11 #In some cases need to explicitly link to x11 lib, needed by glfw3
        -pthread
    )

    #log_analyzer_tool
    include(${PROJECT_ROOT}/log_analyzer_tool/log_analyzer_tool.cmake)

    #include test_log_analyzer_tool
    include(${PROJECT_ROOT}/log_analyzer_tool/test_log_analyzer_tool.cmake)

    #test app
    add_executable(test_app
    ${PROJECT_SOURCE_DIR}/imgui/examples/example_glfw_opengl3/main.cpp
    )

    target_include_directories(test_app  PUBLIC ${PROJECT_INCLUDE_DIRS})

    target_link_libraries(test_app ${PROJECT_LINK_LIBRARIES})

endif()