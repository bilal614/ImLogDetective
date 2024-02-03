set(LOG_ANALYZER_TOOL log_analyzer_tool)
set(LOG_ANALYZER_TOOL_LIB log_analyzer_tool_lib)
set(LOG_ANALYZER_TOOL_DIR ${PROJECT_SOURCE_DIR}/log_analyzer_tool)

find_package(ZLIB REQUIRED)

if(${ZLIB_FOUND})
    add_library(${LOG_ANALYZER_TOOL_LIB} STATIC
        ${LOG_ANALYZER_TOOL_DIR}/src/dearimgui/IOContext.cxx
        ${LOG_ANALYZER_TOOL_DIR}/src/dearimgui/GlfwBackendBinding.cxx
        ${LOG_ANALYZER_TOOL_DIR}/src/dearimgui/ListTreeWidget.cxx
        ${LOG_ANALYZER_TOOL_DIR}/src/dearimgui/MainViewPort.cxx
        ${LOG_ANALYZER_TOOL_DIR}/src/dearimgui/TabBar.cxx
        ${LOG_ANALYZER_TOOL_DIR}/src/dearimgui/ImGuiTextFilterWrapper.cxx
        ${LOG_ANALYZER_TOOL_DIR}/src/dearimgui/WidgetFactory.cxx
        ${LOG_ANALYZER_TOOL_DIR}/src/event_handling/EventLoop.cxx
        ${LOG_ANALYZER_TOOL_DIR}/src/views/FileListView.cxx
        ${LOG_ANALYZER_TOOL_DIR}/src/views/SelectionMenuBar.cxx
        ${LOG_ANALYZER_TOOL_DIR}/src/views/FolderSelectionPopup.cxx
        ${LOG_ANALYZER_TOOL_DIR}/src/LogAnalyzerToolDefs.cxx
        ${LOG_ANALYZER_TOOL_DIR}/src/views/LogFilterView.cxx
        ${LOG_ANALYZER_TOOL_DIR}/src/views/LogView.cxx
        ${LOG_ANALYZER_TOOL_DIR}/src/presenters/MainPresenter.cxx
        ${LOG_ANALYZER_TOOL_DIR}/src/presenters/FileListPresenter.cxx
        ${LOG_ANALYZER_TOOL_DIR}/src/presenters/LogFilePresenter.cxx
        ${LOG_ANALYZER_TOOL_DIR}/src/presenters/LogDataModelFactory.cxx
        ${LOG_ANALYZER_TOOL_DIR}/src/presenters/LogFileTabsPresenter.cxx
        ${LOG_ANALYZER_TOOL_DIR}/src/models/GzipFile.cxx
        ${LOG_ANALYZER_TOOL_DIR}/src/models/LogDataModel.cxx
        ${LOG_ANALYZER_TOOL_DIR}/src/models/LogFileParser.cxx
    )

    target_include_directories(${LOG_ANALYZER_TOOL_LIB} PRIVATE 
        ${PROJECT_INCLUDE_DIRS}
        ${ZLIB_INCLUDE_DIRS}
    )

    target_include_directories(${LOG_ANALYZER_TOOL_LIB} PUBLIC 
        ${LOG_ANALYZER_TOOL_DIR}/inc/ 
    )

    target_link_libraries(${LOG_ANALYZER_TOOL_LIB} 
        ${PROJECT_LINK_LIBRARIES}
        ${ZLIB_LIBRARIES}
    )

    add_executable(${LOG_ANALYZER_TOOL}
        ${LOG_ANALYZER_TOOL_DIR}/src/main.cxx
    )

    target_include_directories(${LOG_ANALYZER_TOOL} PUBLIC 
        ${LOG_ANALYZER_TOOL_LIB}
    )

    target_link_libraries(${LOG_ANALYZER_TOOL} 
        ${LOG_ANALYZER_TOOL_LIB}
    )

else()

    message("Missing ZLIB dependencies NOT FOUND!!!")

endif()
