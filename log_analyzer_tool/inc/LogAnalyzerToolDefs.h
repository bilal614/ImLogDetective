#pragma once

#include <stddef.h>

namespace LogAnalyzerTool
{
    namespace Common {
        extern const char* OkBtn;
        extern const char* CloseBtn;
        extern const char* CopyBtn;
    }

    namespace WindowDefs {
        extern const char* ApplicationName;
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
        constexpr float SmallPopupWindowRelativeToMain_X = 0.25f;
        constexpr float SmallPopupWindowRelativeToMain_Y = 0.125f;
        constexpr float LargePopupWindowRelativeToMain_X = 0.40f;
        constexpr float LargePopupWindowRelativeToMain_Y = 0.35f;
        constexpr float ScaleFactorUpperBound = 2.0f;
        constexpr float ScaleFactorLowerBound = 1.0f;
        constexpr float ScaleFactorChangeSensitivity = 0.05f;
        constexpr size_t MaxTextboxInputLength{4096};

        constexpr float MainBodyRelativeToMainWinPos_X = 0.10f;
        constexpr float MainBodyRelativeToMainWinSize_X = 0.89f;

        constexpr float SidebarRelativeToMainWinSize_X = 0.10f;

        constexpr float MainContentRelativeToMainWinSize_Y = 0.95f;
    }

    namespace SelectFolderDefs {
        extern const char* Name;
        constexpr float TextBoxWidth = 400.0f;
    }

    namespace CopyLogsDefs {
        extern const char* Name;
        extern const char* EnterPass;
        constexpr float TextBoxWidth = 350.0f;
    }

    namespace ProtectedInputDefs{
        extern const char* Name;
        extern const char* Prompt;
        constexpr float TextBoxWidth = 250.0f;
        constexpr float PopupWidth = 350.0f;
        constexpr float PopupHeight = 200.0f;
    }

    namespace ErrorMessage {
        extern const char* InvalidDirectory;
    }

}