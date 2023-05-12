#include "models/LogDataModel.h"
#include <memory>
#include <string_view>

namespace LogAnalyzerTool
{


struct LogDataModel::Impl
{
    Impl(const std::string& dataSource);
    ~Impl() = default;

    const std::string dataSource;
    std::vector<std::string> logData;
};


LogDataModel::Impl::Impl(const std::string& dataSource) :
    dataSource{dataSource}
{

}

LogDataModel::LogDataModel(const std::string& dataSource) :
    p{std::make_unique<Impl>(dataSource)}
{

}

LogDataModel::~LogDataModel() = default;

void LogDataModel::addLogData(std::string_view dataLine)
{
    p->logData.emplace_back(dataLine);
}

void LogDataModel::addMultipleLogData(const std::vector<std::string>&& data)
{
    std::move(data.begin(), data.end(), std::back_inserter(p->logData));
}

std::vector<std::string_view> LogDataModel::getLogData()
{
    //TODO Currently use dummy data for testing\development
    std::vector<std::string_view> data
    {
        "12:04:09,138 - DEBUG - Foo: - Aut labore sunt est deserunt totam ut velit vitae",
        "12:04:09,138 - DEBUG - Foo: - Lorem ipsum dolor sit amet",
        "12:04:09,140 - WARNING - Fubar - Ea consequatur galisum qui voluptas voluptatem sed vitae quia",
        "12:04:09,140 - INFO - Bar - Sit similique sint ut earum saepe",
        "12:04:09,154 - ERROR - Yoo - Ut velit praesentium et minus dicta in",
        "12:04:09,160 - INFO - Bar - Quia aut harum enim eos rerum nulla ut cupiditate unde ea quam placeat",
        "12:04:09,164 - WARNING - Aperiam - Et soluta asperiores sit eaque voluptatibus et nesciunt repudiandae qui aperiam",
        "12:04:10,154 - ERROR - Yoo - Ut velit praesentium et minus dicta in",
        "12:04:11,138 - DEBUG - Foo: - Aut labore sunt est deserunt totam ut velit vitae",
        "12:04:11,138 - DEBUG - Foo: - Lorem ipsum dolor sit amet",
        
    };

    return data;
}


}