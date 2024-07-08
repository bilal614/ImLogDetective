cmake_minimum_required (VERSION 3.16)

set(IM_LOG_DETECTIVE ImLogDetective)
set(IM_LOG_DETECTIVE_LIB ImLogDetective_lib)
set(IM_LOG_DETECTIVE_DIR ${PROJECT_ROOT}/ImLogDetective)

#ImLogDetective
include(${IM_LOG_DETECTIVE_DIR}/ImLogDetective.cmake)

#TestImLogDetective
include(${IM_LOG_DETECTIVE_DIR}/TestImLogDetective.cmake)

#Post-build
set(FONTS_DIR ${IM_LOG_DETECTIVE_DIR}/assets/fonts)

add_custom_command(TARGET ${IM_LOG_DETECTIVE} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${FONTS_DIR} $<TARGET_FILE_DIR:${IM_LOG_DETECTIVE}>/fonts
)

set(ICONS_DIR ${IM_LOG_DETECTIVE_DIR}/assets/icons)

add_custom_command(TARGET ${IM_LOG_DETECTIVE} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${ICONS_DIR} $<TARGET_FILE_DIR:${IM_LOG_DETECTIVE}>/icons
)
