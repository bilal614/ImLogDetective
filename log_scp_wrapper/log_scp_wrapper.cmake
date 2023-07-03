set(LOG_SCP_WRAPPER log_scp_wrapper)
set(LOG_SCP_WRAPPER_DIR ${PROJECT_SOURCE_DIR}/log_scp_wrapper)


add_library(${LOG_SCP_WRAPPER}
    ${LOG_SCP_WRAPPER_DIR}/src/PtyMaster.cxx
    ${LOG_SCP_WRAPPER_DIR}/src/Socket.cxx
)

target_include_directories(${LOG_SCP_WRAPPER} PUBLIC 
    ${LOG_SCP_WRAPPER_DIR}/inc/ 
)

#target_link_libraries(${LOG_SCP_WRAPPER}
#)