find_package(libssh2 CONFIG REQUIRED)

set(LOG_FETCHING_TOOL log_fetching_tool)
set(LOG_FETCHING_TOOL_DIR ${PROJECT_SOURCE_DIR}/log_fetching_tool)

if(libssh2_FOUND)

    add_library(${LOG_FETCHING_TOOL} 
        ${LOG_FETCHING_TOOL_DIR}/src/Authentication.cxx
        ${LOG_FETCHING_TOOL_DIR}/src/ForwardChannel.cxx
        ${LOG_FETCHING_TOOL_DIR}/src/IOMultiPlexor.cxx
        ${LOG_FETCHING_TOOL_DIR}/src/Socket.cxx
        ${LOG_FETCHING_TOOL_DIR}/src/SshSession.cxx
    )

    target_include_directories(${LOG_FETCHING_TOOL} PUBLIC 
        ${LOG_FETCHING_TOOL_DIR}/inc/ 
    )

    target_link_libraries(${LOG_FETCHING_TOOL}
        libssh2::libssh2
    )

endif()