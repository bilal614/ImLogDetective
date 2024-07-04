
find_package(ZLIB REQUIRED)

if(${ZLIB_FOUND})
    add_library(${IM_LOG_DETECTIVE_LIB} STATIC
        ${IM_LOG_DETECTIVE_DIR}/src/dearimgui/IOContext.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/dearimgui/GlfwBackendBinding.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/dearimgui/ImGuiMenuBarWrapperImpl.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/dearimgui/ImGuiTextFilterWrapperImpl.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/dearimgui/ImGuiWidgetWrapperImpl.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/dearimgui/ListTreeWidgetImpl.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/dearimgui/MainViewPortImpl.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/dearimgui/TabBarImpl.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/views/CopyLogsPopupImpl.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/views/FileListViewImpl.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/views/FolderSelectionPopupImpl.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/views/ProtectedInputPopupImpl.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/views/SelectionMenuBarImpl.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/views/WidgetFactoryImpl.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/ImLogDetectiveDefs.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/views/LogFilterViewImpl.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/views/LogViewImpl.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/presenters/CopyLogsPresenter.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/presenters/MainPresenter.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/presenters/FileListPresenter.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/presenters/LogFilePresenter.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/presenters/LogDataModelFactory.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/presenters/LogFileTabsPresenter.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/models/AssetsConfiguratorImpl.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/models/GzipFileImpl.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/models/LogDataModelImpl.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/models/LogLine.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/models/LogFileParserImpl.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/models/MiniImpl.cxx
    )

    target_include_directories(${IM_LOG_DETECTIVE_LIB} PRIVATE 
        ${DEARIMGUI_INCLUDE_DIRS}
        ${ZLIB_INCLUDE_DIRS}
        ${mINI_INCLUDE_DIR}
        ${LOG_EVENT_HANDLING_LIB}
        ${SCP_WRAPPER_LIB}
        ${STB_INCLUDE_DIRS}
    )

    target_include_directories(${IM_LOG_DETECTIVE_LIB} PUBLIC 
        ${IM_LOG_DETECTIVE_DIR}/inc/ 
    )

    target_link_libraries(${IM_LOG_DETECTIVE_LIB} 
        ${PROJECT_LINK_LIBRARIES}
        ${ZLIB_LIBRARIES}
        ${LOG_EVENT_HANDLING_LIB}
        ${SCP_WRAPPER_LIB}
    )

    add_executable(${IM_LOG_DETECTIVE}
        ${IM_LOG_DETECTIVE_DIR}/src/main.cxx
    )

    target_include_directories(${IM_LOG_DETECTIVE} PUBLIC 
        ${IM_LOG_DETECTIVE_LIB}
    )

    target_link_libraries(${IM_LOG_DETECTIVE} 
        ${IM_LOG_DETECTIVE_LIB}
    )

else()

    message("Missing ZLIB dependencies NOT FOUND!!!")

endif()
