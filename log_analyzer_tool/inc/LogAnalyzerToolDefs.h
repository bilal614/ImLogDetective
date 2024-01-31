#pragma once

#include <string>


namespace LogAnalyzerTool
{
    namespace WindowDefs {
        const std::string LogAnalyzerToolApplicationName {"LoggingAnalyzerTool"};
        const std::string FileListWindow {"FileListWindow"};
        const std::string LogsWindow{"LogsWindow"};
        const std::string LogFilterChildWindow {"LogFilterWindow"};
        const std::string LogFileContentChildWindow {"LogFileContentWindow"};
    }

    namespace MenuBarOptions {
        const std::string SelectFolder{"Select Folder"};
        const std::string FetchRemoteLogs{"Fetch Remote Logs"};
        const std::string ConfigureHiglighting{"Configure Highlighting"};
    }
    namespace Bounds{

        constexpr float PopupWindowRelativeToMain_X = 0.25f;
        constexpr float PopupWindowRelativeToMain_Y = 0.125f;
        constexpr float ScaleFactorUpperBound = 2.0f;
        constexpr float ScaleFactorLowerBound = 1.0f;
        constexpr float ScaleFactorChangeSensitivity = 0.05f;
    }

    namespace SelectFolderPopup {
        const std::string Name{"Select Folder"};
    }

}