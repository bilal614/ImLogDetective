
add_library(${LOG_EVENT_HANDLING_LIB} STATIC
    ${LOG_EVENT_HANDLING_DIR}/src/EventLoop.cxx
)

target_include_directories(${LOG_EVENT_HANDLING_LIB} PUBLIC 
    ${LOG_EVENT_HANDLING_DIR}/inc/ 
)
