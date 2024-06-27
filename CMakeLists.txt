cmake_minimum_required (VERSION 3.16)
project(IM_LOG_DETECTIVE C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_ROOT ${PROJECT_SOURCE_DIR})
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

option(WITH_COVERAGE "Build with coverage" OFF)

if (WITH_COVERAGE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Setting Debug for coverage" FORCE)
    include(CodeCoverage)
    append_coverage_compiler_flags()
endif()

# external modules
set(DEARIMGUI_MODULE ${PROJECT_SOURCE_DIR}/ext/imgui/)
set(STB_MODULE ${PROJECT_SOURCE_DIR}/ext/stb/)
set(MINI_MODULE ${PROJECT_SOURCE_DIR}/ext/mINI/)

find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(PkgConfig REQUIRED)

if(${PKG_CONFIG_FOUND})
    pkg_check_modules(GLFW3 REQUIRED glfw3)
endif()

if(OPENGL_FOUND AND GLFW3_FOUND)

    enable_testing()

    include_directories(
        ${OPENGL_INCLUDE_DIRS}
        ${GLFW3_INCLUDE_DIRS}
    )

    add_library(imgui_glfw_opengl SHARED
        ${DEARIMGUI_MODULE}/imgui.cpp
        ${DEARIMGUI_MODULE}/imgui_draw.cpp
        ${DEARIMGUI_MODULE}/imgui_tables.cpp
        ${DEARIMGUI_MODULE}/imgui_widgets.cpp
        ${DEARIMGUI_MODULE}/backends/imgui_impl_glfw.cpp
        ${DEARIMGUI_MODULE}/backends/imgui_impl_opengl3.cpp
        ${DEARIMGUI_MODULE}/misc/cpp/imgui_stdlib.cpp
    )

    target_include_directories(imgui_glfw_opengl PRIVATE 
        ${DEARIMGUI_MODULE}
    )
    
    set(DEARIMGUI_INCLUDE_DIRS 
        ${DEARIMGUI_MODULE}
        ${DEARIMGUI_MODULE}/backends
    )

    set(STB_INCLUDE_DIRS
        ${STB_MODULE}
    )

    set(PROJECT_LINK_LIBRARIES imgui_glfw_opengl
        ${OPENGL_LIBRARIES}
        ${GLFW3_LIBRARIES}
        ${CMAKE_DL_LIBS} #link to dl lib for dynamic loading
        -lX11 #Needed by glfw3
        -pthread
    )

    # Definitions for ScpWrapper_lib
    set(SCP_WRAPPER_LIB ScpWrapper_lib)
    set(SCP_WRAPPER_DIR ${PROJECT_SOURCE_DIR}/ScpWrapper)
    set(SCP_WRAPPER_INCLUDE_DIR ${SCP_WRAPPER_DIR}/inc/)

    # Definitions for EventHandling_lib 
    set(EVENT_HANDLING_LIB EventHandling_lib)
    set(TEST_EVENT_HANDLING TestEventHandling)
    set(EVENT_HANDLING_DIR ${PROJECT_SOURCE_DIR}/EventHandling)
    set(TEST_EVENT_HANDLING_DIR ${EVENT_HANDLING_DIR}/test/mocks)

    # Definitions for mINI
    set(mINI_INCLUDE_DIR ${MINI_MODULE}/src)

    #EventHandling_lib
    add_subdirectory(${PROJECT_ROOT}/EventHandling)

    #ScpWrapper_lib
    add_subdirectory(${PROJECT_ROOT}/ScpWrapper)

    #ImLogDetective
    add_subdirectory(${PROJECT_ROOT}/ImLogDetective)

    #log_fetching_tool
    #include(${PROJECT_ROOT}/log_fetching_tool/log_fetching_tool.cmake)

    #include test_log_fetching_tool
    #include(${PROJECT_ROOT}/log_fetching_tool/test_log_fetching_tool.cmake)

    #test app
    add_executable(test_app
        ${DEARIMGUI_MODULE}/examples/example_glfw_opengl3/main.cpp
        ${DEARIMGUI_MODULE}/imgui_demo.cpp
    )

    target_include_directories(test_app  PUBLIC ${DEARIMGUI_INCLUDE_DIRS})

    target_link_libraries(test_app ${PROJECT_LINK_LIBRARIES})

    if (WITH_COVERAGE)
        set(GCOVR_ADDITIONAL_ARGS --print-summary)
        setup_target_for_coverage_gcovr_xml(
            NAME "coverage-gcov"
            EXECUTABLE ctest
            BASE_DIRECTORY "${PROJECT_ROOT}"
            EXCLUDE "/usr/*" "ext/*")

        setup_target_for_coverage_lcov(
            NAME "coverage-lcov"
            EXECUTABLE ctest
            BASE_DIRECTORY "${PROJECT_ROOT}"
            EXCLUDE "/usr/*" "ext/*")
    endif()

endif()