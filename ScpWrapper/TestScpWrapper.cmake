set(TEST_SCP_WRAPPER TestScpWrapper)
set(TEST_SCP_WRAPPER_DIR ${SCP_WRAPPER_DIR}/test)

find_package(GTest REQUIRED)

if(GTest_FOUND AND LIBSSH2_FOUND)
    add_executable(${TEST_SCP_WRAPPER}
        ${TEST_SCP_WRAPPER_DIR}/TestPtyMaster.cxx
        ${TEST_SCP_WRAPPER_DIR}/TestScpExecutor.cxx
        ${TEST_SCP_WRAPPER_DIR}/main.cxx
    )

    target_include_directories(${TEST_SCP_WRAPPER} PUBLIC 
        ${SCP_WRAPPER_LIB}
    )

    target_link_libraries(${TEST_SCP_WRAPPER}
        ${SCP_WRAPPER_LIB}
        Threads::Threads
        GTest::gtest 
        GTest::gtest_main 
        GTest::gmock 
        GTest::gmock_main)

    gtest_discover_tests(${TEST_SCP_WRAPPER} WORKING_DIRECTORY ${SCP_WRAPPER_DIR})

endif()