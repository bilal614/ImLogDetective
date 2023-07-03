set(TEST_LOG_SCP_WRAPPER test_log_scp_wrapper)
set(LOG_SCP_WRAPPER_DIR ${PROJECT_SOURCE_DIR}/log_scp_wrapper)
set(TEST_LOG_SCP_WRAPPER_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/log_scp_wrapper/test)

message(LOG_SCP_WRAPPER_DIR="${LOG_SCP_WRAPPER_DIR}")

enable_testing()

include(${PROJECT_ROOT}/log_scp_wrapper/find_libssh2.cmake)

#find_package(libssh2 CONFIG REQUIRED)

find_package(GTest REQUIRED)

if(GTest_FOUND AND LIBSSH2_FOUND)
    add_executable(${TEST_LOG_SCP_WRAPPER}
        ${LOG_SCP_WRAPPER_DIR}/src/PtyMaster.cxx
        ${LOG_SCP_WRAPPER_DIR}/test/TestPtyMaster.cxx
        ${LOG_SCP_WRAPPER_DIR}/test/main.cxx
    )

    target_include_directories(${TEST_LOG_SCP_WRAPPER} PUBLIC 
        ${LOG_SCP_WRAPPER_DIR}/inc/
        ${TEST_LOG_SCP_WRAPPER_DIR_INCLUDE_DIR}
        ${LIBSSH2_INCLUDE_DIR}
    )

    target_link_libraries(${TEST_LOG_SCP_WRAPPER}
        -pthread
        GTest::gtest 
        GTest::gtest_main 
        GTest::gmock 
        GTest::gmock_main
        ${LIBSSH2_LIB})

    include(GoogleTest)
    gtest_discover_tests(${TEST_LOG_SCP_WRAPPER})

endif()