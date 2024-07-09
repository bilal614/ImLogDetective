set(TEST_LOG_FETCHING_TOOL TestLogFetchingTool)


find_package(GTest REQUIRED)

if(GTest_FOUND AND LIBSSH2_FOUND)
    add_executable(${TEST_LOG_FETCHING_TOOL}
        ${LOG_FETCHING_TOOL_DIR}/src/Authentication.cxx
        ${LOG_FETCHING_TOOL_DIR}/src/ForwardChannel.cxx
        ${LOG_FETCHING_TOOL_DIR}/src/IOMultiPlexor.cxx
        ${LOG_FETCHING_TOOL_DIR}/src/Socket.cxx
        ${LOG_FETCHING_TOOL_DIR}/src/SshSession.cxx
        ${LOG_FETCHING_TOOL_DIR}/test/TestAuthentication.cxx
        ${LOG_FETCHING_TOOL_DIR}/test/TestForwardChannel.cxx
        ${LOG_FETCHING_TOOL_DIR}/test/TestSocket.cxx
        ${LOG_FETCHING_TOOL_DIR}/test/main.cxx
    )

    target_include_directories(${TEST_LOG_FETCHING_TOOL} PUBLIC 
        ${LOG_FETCHING_TOOL_DIR}/inc/
    )

    target_link_libraries(${TEST_LOG_FETCHING_TOOL}
        ${LIBSSH2_LIBRARIES}
        Threads::Threads
        GTest::gtest 
        GTest::gtest_main 
        GTest::gmock 
        GTest::gmock_main)

    gtest_discover_tests(${TEST_LOG_FETCHING_TOOL} WORKING_DIRECTORY ${LOG_FETCHING_TOOL_DIR})

endif()