#include "LogAnalyzerToolDefs.h"
#include <string>

namespace LogAnalyzerTool
{
    namespace WindowDefs {
        const char* LogAnalyzerToolApplicationName {"LoggingAnalyzerTool"};
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

    namespace SelectFolderPopup {
        const char* Name{"Select Folder"};
        const char* OkBtn{"OK"};
        const char* CloseBtn{"Close"};
    }

    namespace ErrorMessage {
        const char* InvalidDirectory {"Not a valid directory path."};
    }

}