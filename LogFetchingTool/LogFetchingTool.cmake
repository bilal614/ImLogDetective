
pkg_check_modules(LIBSSH2 REQUIRED libssh2)

#include(${LOG_FETCHING_TOOL_DIR}/find_libssh2.cmake)

if(LIBSSH2_FOUND)

    add_library(${LOG_FETCHING_TOOL_LIB} 
        ${LOG_FETCHING_TOOL_DIR}/src/Authentication.cxx
        ${LOG_FETCHING_TOOL_DIR}/src/ForwardChannel.cxx
        ${LOG_FETCHING_TOOL_DIR}/src/IOMultiPlexor.cxx
        ${LOG_FETCHING_TOOL_DIR}/src/Socket.cxx
        ${LOG_FETCHING_TOOL_DIR}/src/SshSession.cxx
    )

    target_include_directories(${LOG_FETCHING_TOOL_LIB} PUBLIC 
        ${LOG_FETCHING_TOOL_DIR}/inc/ 
        ${LIBSSH2_INCLUDE_DIRS}
    )

    target_link_libraries(${LOG_FETCHING_TOOL_LIB}
        ${LIBSSH2_LIBRARIES}
    )

endif()