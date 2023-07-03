set(TEST_LOG_FETCHING_TOOL test_log_fetching_tool)
set(LOG_FETCHING_TOOL_DIR ${PROJECT_SOURCE_DIR}/log_fetching_tool)
set(TEST_LOG_FETCHING_TOOL_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/log_fetching_tool/test)

message(LOG_FETCHING_TOOL_DIR="${LOG_FETCHING_TOOL_DIR}")

enable_testing()

find_package(libssh2 CONFIG REQUIRED)

find_package(GTest REQUIRED)

if(GTest_FOUND AND libssh2_FOUND)
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
        ${TEST_LOG_FETCHING_TOOL_INCLUDE_DIR}
    )

    target_link_libraries(${TEST_LOG_FETCHING_TOOL}
        ssh
        -pthread
        GTest::gtest 
        GTest::gtest_main 
        GTest::gmock 
        GTest::gmock_main
        libssh2::libssh2)

    include(GoogleTest)
    gtest_discover_tests(${TEST_LOG_FETCHING_TOOL})

endif()