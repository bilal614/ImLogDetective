#include "models/LogLine.h"
#include <unordered_map>

namespace{
    std::unordered_map<ImLogDetective::LogLevel, ImLogDetective::TextColor> logLevelToTextColor {
        {ImLogDetective::LogLevel::Unknown,     ImLogDetective::TextColor::Yellow},
        {ImLogDetective::LogLevel::Debug,       ImLogDetective::TextColor::White},
        {ImLogDetective::LogLevel::Info,        ImLogDetective::TextColor::White},
        {ImLogDetective::LogLevel::Warning,     ImLogDetective::TextColor::Orange},
        {ImLogDetective::LogLevel::Error,       ImLogDetective::TextColor::Red}
    };
}

namespace ImLogDetective
{

LogLine::LogLine() :
    LogLine{std::string{}, LogLevel::Unknown}
{
}

LogLine::LogLine(const std::string line, LogLevel level) :
    logLine{line},
    level{level},
    color{logLevelToTextColor[level]},
    selected{false}
{
}

bool LogLine::operator==(const LogLine& data) const
{
    return data.logLine == logLine && data.level == level && data.selected == selected;
}

}