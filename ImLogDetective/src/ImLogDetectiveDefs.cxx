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

    namespace MenuBarOptions {
        const char* SelectFolder{"Select Folder"};
        const char* FetchRemoteLogs{"Fetch Remote Logs"};
        const char* ConfigureHiglighting{"Configure Highlighting"};
    }

    namespace SelectFolderDefs {
        const char* Name{"Select Folder"};
    }

    namespace CopyLogsDefs {
        const char* Name{"Copy Remote Logs"};
        const char* EnterPass{"Enter pass"};
    }

    namespace ProtectedInputDefs{
        const char* Name{"Enter pass"};
        const char* Prompt{"Please enter "};
    }

    namespace ErrorMessage {
        const char* InvalidDirectory {"Not a valid directory path."};
    }

}