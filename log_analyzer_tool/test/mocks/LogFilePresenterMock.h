#pragma once

#include "presenters/ILogFilePresenter.h"
#include "models/ILogDataModel.h"
#include "gmock/gmock.h"

namespace TestImLogDetective {

class LogFilePresenterMock : public ImLogDetective::ILogFilePresenter 
{
public:
    MOCK_METHOD(void, update, (const std::filesystem::path&, bool, ImLogDetective::ILogDataModel&));
};

}