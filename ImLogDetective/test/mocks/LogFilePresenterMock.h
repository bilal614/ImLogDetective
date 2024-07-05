#pragma once

#include "presenters/LogFilePresenter.h"
#include "models/LogDataModel.h"
#include "gmock/gmock.h"

namespace TestImLogDetective {

class LogFilePresenterMock : public ImLogDetective::LogFilePresenter 
{
public:
    MOCK_METHOD(void, update, (const std::filesystem::path&, bool, ImLogDetective::LogDataModel&));
};

}