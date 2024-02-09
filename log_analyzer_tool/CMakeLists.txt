cmake_minimum_required (VERSION 3.16)

set(LOG_ANALYZER_TOOL log_analyzer_tool)
set(LOG_ANALYZER_TOOL_LIB log_analyzer_tool_lib)
set(LOG_ANALYZER_TOOL_DIR ${PROJECT_SOURCE_DIR}/log_analyzer_tool)

#log_analyzer_tool
include(${PROJECT_ROOT}/log_analyzer_tool/log_analyzer_tool.cmake)

#test_log_analyzer_tool
include(${PROJECT_ROOT}/log_analyzer_tool/test_log_analyzer_tool.cmake)