#include "ImLogDetectiveDefs.h"
#include <string>

namespace ImLogDetective
{
    namespace Common {
        const char* OkBtn{"OK"};
        const char* CloseBtn{"Close"};
        const char* CopyBtn{"Copy"};
    }

    namespace WindowDefs {
        const char* ApplicationName {"ImLogDetective"};
        const char* FileListWindow {"FileListWindow"};
        const char* LogsWindow{"LogsWindow"};
        const char* LogFilterChildWindow {"LogFilterWindow"};
        const char* LogFileContentChildWindow {"LogFileContentWindow"};
    }

    namespace IniDefs{
        const char* IniFile{"ImLogDetective.ini"};
        namespace CopyLogsSection {
            const char* Name{"CopyLogs"};
            const char* SrcHostPath{"src_host_path"};
            const char* DestinationPath{"destination_path"};
            const char* JumpHost1{"jump_host1"};
            const char* JumpHost2{"jump_host2"};
            const char* KeyFilePath1{"key_file_path1"};
            const char* KeyFilePath2{"key_file_path2"};
        }
        namespace SelectedFolderSection {
            const char* Name{"SelectedFolder"};
            const char* LogDataFolder{"log_data_folder"};
        }
    }

    namespace Font{
        const char* DefaultFontTffPath{"fonts/Roboto/Roboto-Regular.ttf"};
    }

    namespace Icons{
        const char* ImLogDetectiveIcon{"icons/ImLogDetective_icon.png"};
    }

    namespace MenuBar{
        const char* Name{"Menu"};
        const char* ScaleLabel{"Scale"};
    }

    namespace MenuBarOptions {
        const char* SelectFolder{"Select Folder"};
        const char* FetchRemoteLogs{"Fetch Remote Logs"};
        const char* ConfigureHiglighting{"Configure Highlighting"};
    }

    namespace SelectFolderDefs {
        const char* Name{"Select Folder"};
        const char* ClearLogs{"Clear Logs"};
    }

    namespace CopyLogsDefs {
        const char* Name{"Copy Remote Logs"};
        const char* EnterPass{"Enter pass"};
        const char* SrcDestGroup{"Directories"};
        const char* SrcHostPath{"Source Host Path"};
        const char* DestDir{"Destination Directory"};
        const char* JumpHostGroup{"Jump Host"};
        const char* JumpHost1{"Jump Host 1"};
        const char* JumpHost2{"Jump Host 2"};
        const char* KeyFilePath1{"Key File Path 1"};
        const char* KeyFilePath2{"Key File Path 2"};
    }

    namespace ProtectedInputDefs{
        const char* Name{"Enter pass"};
        const char* Prompt{"Please enter "};
    }

    namespace ErrorMessage {
        const char* InvalidDirectory {"Not a valid directory path."};
    }

    namespace LogFilterDefs {
        const char* DebugCheckBoxLabel{"DEBUG"};
        const char* InfoCheckBoxLabel{"INFO"};
        const char* WarningCheckBoxLabel{"WARNING"};
        const char* ErrorCheckBoxLabel{"ERROR"};
    }

}