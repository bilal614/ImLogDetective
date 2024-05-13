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
        const char* Name{"Enter Pass"};
        const char* Prompt{"Please enter password\\passphrase"};
    }

    namespace ErrorMessage {
        const char* InvalidDirectory {"Not a valid directory path."};
    }

}