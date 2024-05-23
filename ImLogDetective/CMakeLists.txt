cmake_minimum_required (VERSION 3.16)

set(IM_LOG_DETECTIVE ImLogDetective)
set(IM_LOG_DETECTIVE_LIB ImLogDetective_lib)
set(IM_LOG_DETECTIVE_DIR ${PROJECT_SOURCE_DIR}/ImLogDetective)

#ImLogDetective
include(${PROJECT_ROOT}/ImLogDetective/ImLogDetective.cmake)

#TestImLogDetective
include(${PROJECT_ROOT}/ImLogDetective/TestImLogDetective.cmake)

#Post-build 
set(FONTS_DIR ${IM_LOG_DETECTIVE_DIR}/fonts)

add_custom_command(TARGET ${IM_LOG_DETECTIVE} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${FONTS_DIR} $<TARGET_FILE_DIR:${IM_LOG_DETECTIVE}>/fonts
)
