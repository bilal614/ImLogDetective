find_package(GTest REQUIRED)

if(GTest_FOUND)
    add_executable(${TEST_EVENT_HANDLING}
        ${EVENT_HANDLING_DIR}/test/src/TestEventLoop.cxx
        ${EVENT_HANDLING_DIR}/test/main.cxx
    )

    target_include_directories(${TEST_EVENT_HANDLING} PUBLIC 
        ${EVENT_HANDLING_LIB}
    )

    target_link_libraries(${TEST_EVENT_HANDLING} 
        ${EVENT_HANDLING_LIB}
        GTest::gtest 
        GTest::gtest_main 
        GTest::gmock 
        GTest::gmock_main
    )

    add_test(NAME TEST_EVENT_HANDLING COMMAND ${TEST_EVENT_HANDLING})

endif()