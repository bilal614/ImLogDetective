find_package(libssh2 CONFIG REQUIRED)

# add_library(libssh2 STATIC IMPORTED GLOBAL)

# set_property(TARGET libssh2 PROPERTY
#     IMPORTED_LOCATION "/usr/local/lib/libssh2.a"
# )

# target_include_directories(libssh2 PUBLIC
#     "/usr/local/include/"
# )

set(LOG_FETCHING_TOOL log_fetching_tool)
set(LOG_FETCHING_TOOL_DIR ${PROJECT_SOURCE_DIR}/log_fetching_tool)

if(libssh2_FOUND)
    message("libssh2 FOUND!!")
endif()

# add_library(${LOG_FETCHING_TOOL} 
#     ${LOG_FETCHING_TOOL_DIR}/src/Authentication.cxx
#     ${LOG_FETCHING_TOOL_DIR}/src/SshSession.cxx
# )

#link_directories(${LIBSSH_LIBRARY_DIR})

# target_include_directories(${LOG_FETCHING_TOOL} PUBLIC 
#     ${LIBSSH_INCLUDE_DIRS}    
#     ${LOG_FETCHING_TOOL_DIR}/inc/ 
# )

# target_link_libraries(${LOG_FETCHING_TOOL}
#     libssh2::libssh2
# )
# target_link_libraries(${LOG_FETCHING_TOOL}
#     libssh2::libssh2
# )