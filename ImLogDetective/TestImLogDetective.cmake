set(TEST_IM_LOG_DETECTIVE TestImLogDetective)
set(TEST_IM_LOG_DETECTIVE_INCLUDE_DIR ${IM_LOG_DETECTIVE_DIR}/test/inc ${IM_LOG_DETECTIVE_DIR}/test/mocks)

enable_testing()
find_package(GTest REQUIRED)

if(GTest_FOUND)
    # Copy Test Data
    file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/test_data)
    file(COPY_FILE ${IM_LOG_DETECTIVE_DIR}/test/data/test.txt.gz ${CMAKE_CURRENT_BINARY_DIR}/test_data/test.txt.gz ONLY_IF_DIFFERENT)

    add_executable(${TEST_IM_LOG_DETECTIVE}
        ${IM_LOG_DETECTIVE_DIR}/test/src/models/TestGzipFileParsers.cxx
        ${IM_LOG_DETECTIVE_DIR}/test/src/presenters/TestLogFilePresenter.cxx
        ${IM_LOG_DETECTIVE_DIR}/test/src/presenters/TestLogFileTabsPresenter.cxx
        ${IM_LOG_DETECTIVE_DIR}/test/src/presenters/TestMainPresenter.cxx
        ${IM_LOG_DETECTIVE_DIR}/test/src/TestUtility.cxx
        ${IM_LOG_DETECTIVE_DIR}/test/src/views/TestFolderSelectionPopup.cxx
        ${IM_LOG_DETECTIVE_DIR}/test/main.cxx
    )

    target_include_directories(${TEST_IM_LOG_DETECTIVE} PUBLIC 
        ${IM_LOG_DETECTIVE_LIB}
        ${TEST_IM_LOG_DETECTIVE_INCLUDE_DIR}
        ${PROJECT_INCLUDE_DIRS}
        ${TEST_LOG_EVENT_HANDLING_DIR}
    )

    target_link_libraries(${TEST_IM_LOG_DETECTIVE} 
        ${IM_LOG_DETECTIVE_LIB}
        GTest::gtest 
        GTest::gtest_main 
        GTest::gmock 
        GTest::gmock_main
    )

    include(GoogleTest)
        gtest_discover_tests(${TEST_IM_LOG_DETECTIVE}
    )

endif()