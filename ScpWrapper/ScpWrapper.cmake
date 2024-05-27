
add_library(${SCP_WRAPPER_LIB}
    ${SCP_WRAPPER_DIR}/src/AuthenticationWorkFlow.cxx
    ${SCP_WRAPPER_DIR}/src/PtyMaster.cxx
    ${SCP_WRAPPER_DIR}/src/ScpExecutor.cxx
)

target_include_directories(${SCP_WRAPPER_LIB} PUBLIC 
    ${SCP_WRAPPER_INCLUDE_DIR}
    ${EVENT_HANDLING_LIB}
)

target_link_libraries(${SCP_WRAPPER_LIB} 
    ${EVENT_HANDLING_LIB}
)