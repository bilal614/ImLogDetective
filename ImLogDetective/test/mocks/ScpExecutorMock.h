#pragma once

#include "ScpWrapper/IScpExecutor.h"
#include "ScpWrapper/IAuthenticationWorkFlow.h"
#include "ScpWrapper/RemoteHost.h"
#include "gmock/gmock.h"
#include <filesystem>

namespace TestImLogDetective {

class ScpExecutorMock : public ImLogDetective::IScpExecutor 
{
public:
    MOCK_METHOD(bool, setSourceRemoteHostPath, (const std::string&));
    MOCK_METHOD(ImLogDetective::RemoteHostPath, getSourceRemoteHostPath, ());
    MOCK_METHOD(bool, setDestinationLocalPath, (const std::filesystem::path&));
    MOCK_METHOD(std::filesystem::path, getDestinationLocalPath, ());
    MOCK_METHOD(bool, addIdentityFile, (const std::filesystem::path&));
    MOCK_METHOD(std::unordered_set<std::filesystem::path>, getIdentityFiles, ());
    MOCK_METHOD(bool, addJumpHost, (const std::string&));
    MOCK_METHOD(ImLogDetective::JumpHostsSet, getJumpHosts, ());
    MOCK_METHOD(void, download, ());
    MOCK_METHOD(bool, downloadStarted, ());
    MOCK_METHOD(bool, downloadFinished, ());
    MOCK_METHOD(std::string, prompt,());
    MOCK_METHOD(ImLogDetective::AuthenticationRequest, getAuthenticationRequest, ());
    MOCK_METHOD(bool, passRequired, ());
    MOCK_METHOD(void, enterPass, (const std::string&));
};

}