#pragma once

#include <string>

namespace LogAnalyzerTool
{
    namespace WindowDefs {
        extern const char* LogAnalyzerToolApplicationName;
        extern const char* FileListWindow;
        extern const char* LogsWindow;
        extern const char* LogFilterChildWindow;
        extern const char* LogFileContentChildWindow;
    }

    namespace MenuBarOptions {
        extern const char* SelectFolder;
        extern const char* FetchRemoteLogs;
        extern const char* ConfigureHiglighting;
    }

    namespace Bounds{

        constexpr float PopupWindowRelativeToMain_X = 0.25f;
        constexpr float PopupWindowRelativeToMain_Y = 0.125f;
        constexpr float ScaleFactorUpperBound = 2.0f;
        constexpr float ScaleFactorLowerBound = 1.0f;
        constexpr float ScaleFactorChangeSensitivity = 0.05f;
    }

    namespace SelectFolderPopup {
        extern const char* Name;
    }

    namespace ErrorMessage {
        extern const char* InvalidDirectory;
    }

}