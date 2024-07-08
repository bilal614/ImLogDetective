cmake_minimum_required (VERSION 3.16)

set(LOG_FETCHING_TOOL LogFetchingTool)
set(LOG_FETCHING_TOOL_LIB LogFetchingTool_lib)
set(LOG_FETCHING_TOOL_DIR ${PROJECT_ROOT}/LogFetchingTool)

#log_fetching_tool
include(${LOG_FETCHING_TOOL_DIR}/LogFetchingTool.cmake)

#include test_log_fetching_tool
include(${LOG_FETCHING_TOOL_DIR}/TestLogFetchingTool.cmake)
