
find_package(ZLIB REQUIRED)

if(${ZLIB_FOUND})
    add_library(${IM_LOG_DETECTIVE_LIB} STATIC
        ${IM_LOG_DETECTIVE_DIR}/src/dearimgui/IOContext.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/dearimgui/GlfwBackendBinding.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/dearimgui/ImGuiWidgetWrapper.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/dearimgui/ListTreeWidget.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/dearimgui/MainViewPort.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/dearimgui/TabBar.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/dearimgui/ImGuiTextFilterWrapper.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/views/CopyLogsPopup.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/views/FileListView.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/views/FolderSelectionPopup.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/views/ProtectedInputPopup.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/views/SelectionMenuBar.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/views/WidgetFactory.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/ImLogDetectiveDefs.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/views/LogFilterView.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/views/LogView.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/presenters/CopyLogsPresenter.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/presenters/MainPresenter.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/presenters/FileListPresenter.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/presenters/LogFilePresenter.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/presenters/LogDataModelFactory.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/presenters/LogFileTabsPresenter.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/models/AssetsConfigurator.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/models/GzipFile.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/models/LogDataModel.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/models/LogFileParser.cxx
        ${IM_LOG_DETECTIVE_DIR}/src/models/Mini.cxx
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
