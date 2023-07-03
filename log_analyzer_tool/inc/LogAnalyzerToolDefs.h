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
    namespace Bounds{

        constexpr float PopupWindowRelativeToMain_X = 0.25f;
        constexpr float PopupWindowRelativeToMain_Y = 0.25f;
        constexpr float ScaleFactorUpperBound = 2.0f;
        constexpr float ScaleFactorLowerBound = 1.0f;
        constexpr float ScaleFactorChangeSensitivity = 0.05f;
    }

}