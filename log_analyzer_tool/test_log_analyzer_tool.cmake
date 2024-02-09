set(TEST_LOG_ANALYZER_TOOL test_log_analyzer_tool)
set(LOG_ANALYZER_TOOL_DIR ${PROJECT_SOURCE_DIR}/log_analyzer_tool)
set(TEST_LOG_ANALYZER_TOOL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/log_analyzer_tool/test/inc ${PROJECT_SOURCE_DIR}/log_analyzer_tool/test/mocks)

enable_testing()
find_package(GTest REQUIRED)

if(GTest_FOUND)
    # Copy Test Data
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/test_data)
    file(COPY_FILE ${LOG_ANALYZER_TOOL_DIR}/test/data/test.txt.gz ${CMAKE_CURRENT_BINARY_DIR}/test_data/test.txt.gz ONLY_IF_DIFFERENT)

    add_executable(${TEST_LOG_ANALYZER_TOOL}
        ${LOG_ANALYZER_TOOL_DIR}/test/src/event_handling/TestEventLoop.cxx
        ${LOG_ANALYZER_TOOL_DIR}/test/src/models/TestGzipFileParsers.cxx
        ${LOG_ANALYZER_TOOL_DIR}/test/src/presenters/TestLogFilePresenter.cxx
        ${LOG_ANALYZER_TOOL_DIR}/test/src/presenters/TestLogFileTabsPresenter.cxx
        ${LOG_ANALYZER_TOOL_DIR}/test/src/presenters/TestMainPresenter.cxx
        ${LOG_ANALYZER_TOOL_DIR}/test/src/TestUtility.cxx
        ${LOG_ANALYZER_TOOL_DIR}/test/src/views/TestFolderSelectionPopup.cxx
        ${LOG_ANALYZER_TOOL_DIR}/test/main.cxx
    )

    target_include_directories(${TEST_LOG_ANALYZER_TOOL} PUBLIC 
        ${LOG_ANALYZER_TOOL_LIB}
        ${TEST_LOG_ANALYZER_TOOL_INCLUDE_DIR}
        ${PROJECT_INCLUDE_DIRS}
    )

    target_link_libraries(${TEST_LOG_ANALYZER_TOOL} 
        ${LOG_ANALYZER_TOOL_LIB}
        GTest::gtest 
        GTest::gtest_main 
        GTest::gmock 
        GTest::gmock_main
    )

    include(GoogleTest)
        gtest_discover_tests(${TEST_LOG_ANALYZER_TOOL}
    )

endif()