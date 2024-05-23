cmake_minimum_required (VERSION 3.16)
project(IM_LOG_DETECTIVE C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_ROOT ${PROJECT_SOURCE_DIR})

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(PkgConfig REQUIRED)

if(${PKG_CONFIG_FOUND})
    pkg_check_modules(GLFW3 REQUIRED glfw3)
endif()

if(OPENGL_FOUND AND GLFW3_FOUND)

    include_directories(
        ${OPENGL_INCLUDE_DIRS}
        ${GLFW3_INCLUDE_DIRS}
    )

    add_library(imgui_glfw_opengl SHARED
        ${PROJECT_SOURCE_DIR}/imgui/imgui.cpp
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
    
    set(PROJECT_INCLUDE_DIRS 
        ${PROJECT_SOURCE_DIR}/imgui
        ${PROJECT_SOURCE_DIR}/imgui/backends
    )

    set(PROJECT_LINK_LIBRARIES imgui_glfw_opengl
        ${OPENGL_LIBRARIES}
        ${GLFW3_LIBRARIES}
        ${CMAKE_DL_LIBS} #link to dl lib for dynamic loading
        -lX11 #In some cases need to explicitly link to x11 lib, needed by glfw3
        -pthread
    )

    # Definitions for log_scp_wrapper_lib
    set(LOG_SCP_WRAPPER_LIB log_scp_wrapper_lib)
    set(LOG_SCP_WRAPPER_DIR ${PROJECT_SOURCE_DIR}/log_scp_wrapper)
    set(LOG_SCP_WRAPPER_INCLUDE_DIR ${LOG_SCP_WRAPPER_DIR}/inc/)

    # Definitions for log_event_handling_lib 
    set(LOG_EVENT_HANDLING_LIB log_event_handling_lib)
    set(TEST_LOG_EVENT_HANDLING test_log_event_handling)
    set(LOG_EVENT_HANDLING_DIR ${PROJECT_SOURCE_DIR}/log_event_handling)
    set(TEST_LOG_EVENT_HANDLING_DIR ${LOG_EVENT_HANDLING_DIR}/test/mocks)

    # Definitions for mINI
    set(mINI_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/mINI/src)

    #log_event_handling
    add_subdirectory(${PROJECT_ROOT}/log_event_handling)

    #log_scp_wrapper
    add_subdirectory(${PROJECT_ROOT}/log_scp_wrapper)

    #ImLogDetective
    add_subdirectory(${PROJECT_ROOT}/ImLogDetective)

    #log_fetching_tool
    #include(${PROJECT_ROOT}/log_fetching_tool/log_fetching_tool.cmake)

    #include test_log_fetching_tool
    #include(${PROJECT_ROOT}/log_fetching_tool/test_log_fetching_tool.cmake)

    #test app
    add_executable(test_app
        ${PROJECT_SOURCE_DIR}/imgui/examples/example_glfw_opengl3/main.cpp
        ${PROJECT_SOURCE_DIR}/imgui/imgui_demo.cpp
    )

    target_include_directories(test_app  PUBLIC ${PROJECT_INCLUDE_DIRS})

    target_link_libraries(test_app ${PROJECT_LINK_LIBRARIES})

endif()