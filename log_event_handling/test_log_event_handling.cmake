
enable_testing()
find_package(GTest REQUIRED)

if(GTest_FOUND)
    add_executable(${TEST_LOG_EVENT_HANDLING}
        ${LOG_EVENT_HANDLING_DIR}/test/src/TestEventLoop.cxx
        ${LOG_EVENT_HANDLING_DIR}/test/main.cxx
    )

    target_include_directories(${TEST_LOG_EVENT_HANDLING} PUBLIC 
        ${LOG_EVENT_HANDLING_LIB}
    )

    target_link_libraries(${TEST_LOG_EVENT_HANDLING} 
        ${LOG_EVENT_HANDLING_LIB}
        GTest::gtest 
        GTest::gtest_main 
        GTest::gmock 
        GTest::gmock_main
    )

    include(GoogleTest)
        gtest_discover_tests(${TEST_LOG_EVENT_HANDLING}
    )

endif()