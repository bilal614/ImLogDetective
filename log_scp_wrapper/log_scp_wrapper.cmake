
add_library(${LOG_SCP_WRAPPER_LIB}
    ${LOG_SCP_WRAPPER_DIR}/src/PtyMaster.cxx
    ${LOG_SCP_WRAPPER_DIR}/src/Socket.cxx
)

target_include_directories(${LOG_SCP_WRAPPER_LIB} PUBLIC 
    ${LOG_SCP_WRAPPER_INCLUDE_DIR} 
)
