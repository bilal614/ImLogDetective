
add_library(${EVENT_HANDLING_LIB} STATIC
    ${EVENT_HANDLING_DIR}/src/EventLoop.cxx
)

target_include_directories(${EVENT_HANDLING_LIB} PUBLIC 
    ${EVENT_HANDLING_DIR}/inc/ 
)
