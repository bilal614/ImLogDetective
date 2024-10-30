
#ifndef IMLOGDETECTIVE_IMLOGDETECTIVEDEFS_H
#define IMLOGDETECTIVE_IMLOGDETECTIVEDEFS_H

#include <stddef.h>

namespace ImLogDetective
{
    namespace Common {
        extern const char* OkBtn;
        extern const char* CloseBtn;
        extern const char* CopyBtn;
        constexpr size_t MaxTextboxInputLength{4096};
    }

    namespace WindowDefs {
        extern const char* ApplicationName;
        extern const char* FileListWindow;
        extern const char* LogsWindow;
        extern const char* LogFilterChildWindow;
        extern const char* LogFileContentChildWindow;
    }

    namespace Scaling {
        constexpr int MinScaleFactor = 0;
        constexpr int MaxScaleFactor = 5;
        constexpr float ScaleFactorUpperBound = 2.0f;
        constexpr float ScaleFactorLowerBound = 1.0f;
    }

    namespace Font{
        constexpr float DefaultFontPixelSize = 16.0f;
        extern const char* DefaultFontTffPath;
    }

    namespace Icons{
        extern const char* ImLogDetectiveIcon;
    }

    namespace IniDefs{
        extern const char* IniFile;
        namespace CopyLogsSection {
            extern const char* Name;
            extern const char* SrcHostPath;
            extern const char* DestinationPath;
            extern const char* JumpHost1;
            extern const char* JumpHost2;
            extern const char* KeyFilePath1;
            extern const char* KeyFilePath2;
        }
        namespace SelectedFolderSection {
            extern const char* Name;
            extern const char* LogDataFolder;
        }
    }

    namespace MenuBar{
        extern const char* Name;
        extern const char* ScaleLabel;
    }
    namespace MenuBarOptions {
        extern const char* SelectFolder;
        extern const char* FetchRemoteLogs;
        extern const char* ConfigureHiglighting;
    }

    namespace LayoutBounds{
        constexpr float SmallPopupWindowRelativeToMain_X = 0.25f;
        constexpr float SmallPopupWindowRelativeToMain_Y = 0.125f;
        constexpr float LargePopupWindowRelativeToMain_X = 0.40f;
        constexpr float LargePopupWindowRelativeToMain_Y = 0.35f;
        constexpr float ScaleFactorChangeSensitivity = 0.05f;

        constexpr float MainBodyRelativeToMainWinPos_X = 0.10f;
        constexpr float MainBodyRelativeToMainWinSize_X = 0.89f;

        constexpr float SidebarRelativeToMainWinSize_X = 0.10f;

        constexpr float MainContentRelativeToMainWinSize_Y = 0.95f;
    }

    namespace SelectFolderDefs {
        extern const char* Name;
        extern const char* ClearLogs;
        constexpr float TextBoxWidth = 400.0f;
    }

    namespace CopyLogsDefs {
        extern const char* Name;
        extern const char* EnterPass;
        extern const char* SrcDestGroup;
        extern const char* SrcHostPath;
        extern const char* DestDir;
        extern const char* JumpHostGroup;
        extern const char* JumpHost1;
        extern const char* JumpHost2;
        extern const char* KeyFileGroup;
        extern const char* KeyFilePath1;
        extern const char* KeyFilePath2;
        constexpr float TextBoxWidth = 350.0f;
    }

    namespace ProtectedInputDefs{
        extern const char* Name;
        extern const char* Prompt;
        constexpr float TextBoxWidth = 250.0f;
        constexpr float PopupWidth = 600.0f;
        constexpr float PopupHeight = 200.0f;
    }

    namespace ErrorMessage {
        extern const char* InvalidDirectory;
    }

    namespace LogFilterDefs {
        extern const char* DebugCheckBoxLabel;
        extern const char* InfoCheckBoxLabel;
        extern const char* WarningCheckBoxLabel;
        extern const char* ErrorCheckBoxLabel;
    }

}

#endif