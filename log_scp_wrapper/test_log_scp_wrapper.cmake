set(TEST_LOG_SCP_WRAPPER test_log_scp_wrapper)
set(TEST_LOG_SCP_WRAPPER_DIR ${LOG_SCP_WRAPPER_DIR}/test)

enable_testing()

include(${PROJECT_ROOT}/log_scp_wrapper/find_libssh2.cmake)

find_package(GTest REQUIRED)

if(GTest_FOUND AND LIBSSH2_FOUND)
    add_executable(${TEST_LOG_SCP_WRAPPER}
        ${TEST_LOG_SCP_WRAPPER_DIR}/TestPtyMaster.cxx
        ${TEST_LOG_SCP_WRAPPER_DIR}/TestScpExecutor.cxx
        ${TEST_LOG_SCP_WRAPPER_DIR}/main.cxx
    )

    target_include_directories(${TEST_LOG_SCP_WRAPPER} PUBLIC 
        ${LOG_SCP_WRAPPER_LIB}
    )

    target_link_libraries(${TEST_LOG_SCP_WRAPPER}
        ${LOG_SCP_WRAPPER_LIB}
        -pthread
        GTest::gtest 
        GTest::gtest_main 
        GTest::gmock 
        GTest::gmock_main)

    include(GoogleTest)
    gtest_discover_tests(${TEST_LOG_SCP_WRAPPER})

endif()