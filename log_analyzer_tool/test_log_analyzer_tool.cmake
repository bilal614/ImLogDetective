set(TEST_LOG_ANALYZER_TOOL test_log_analyzer_tool)
set(LOG_ANALYZER_TOOL_DIR ${PROJECT_SOURCE_DIR}/log_analyzer_tool)
set(TEST_LOG_ANALYZER_TOOL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/log_analyzer_tool/test)


enable_testing()
find_package(GTest REQUIRED)

if(GTest_FOUND)
    add_executable(${TEST_LOG_ANALYZER_TOOL}
        ${LOG_ANALYZER_TOOL_DIR}/src/event_handling/EventLoop.cxx
        ${LOG_ANALYZER_TOOL_DIR}/test/event_handling/TestEventLoop.cxx
        ${LOG_ANALYZER_TOOL_DIR}/src/presenters/LogFilePresenter.cxx
        ${LOG_ANALYZER_TOOL_DIR}/src/presenters/LogFileTabsPresenter.cxx
        ${LOG_ANALYZER_TOOL_DIR}/test/presenters/TestLogFilePresenter.cxx
        ${LOG_ANALYZER_TOOL_DIR}/test/presenters/TestLogFileTabsPresenter.cxx
        ${LOG_ANALYZER_TOOL_DIR}/test/main.cxx
    )

    target_include_directories(${TEST_LOG_ANALYZER_TOOL} PUBLIC 
        ${LOG_ANALYZER_TOOL_DIR}/inc/
        ${TEST_LOG_ANALYZER_TOOL_INCLUDE_DIR}
        ${PROJECT_INCLUDE_DIRS}
    )

    target_link_libraries(${TEST_LOG_ANALYZER_TOOL} 
        ${PROJECT_LINK_LIBRARIES} 
        GTest::gtest 
        GTest::gtest_main 
        GTest::gmock 
        GTest::gmock_main)

    include(GoogleTest)
    gtest_discover_tests(${TEST_LOG_ANALYZER_TOOL})

endif()