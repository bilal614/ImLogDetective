#pragma once

#include "views/FileListView.h"
#include "gmock/gmock.h"

namespace TestImLogDetective {

class FileListViewMock : public ImLogDetective::FileListView 
{
public:
    MOCK_METHOD(void, draw,(const std::vector<std::string>&));
};

}