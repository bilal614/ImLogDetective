//#include <libssh/libssh.h>
#include <algorithm>
#include <cctype>
#include <libssh2.h>
#include "Authentication.h"
#include "IAuthentication.h"
#include "ISshSession.h"

#include <sstream>
#include <unordered_map>
#include <type_traits>
#include <regex>

#include <iostream>

namespace {

std::unordered_map<std::string, LogFetchingTool::AuthenticationMethod> authenticationMethods {
    {"hostbased", LogFetchingTool::AuthenticationMethod::HostBased},
    {"interactive", LogFetchingTool::AuthenticationMethod::Interactive},
    {"password", LogFetchingTool::AuthenticationMethod::Password},
    {"publickey", LogFetchingTool::AuthenticationMethod::PublicKey}
};

int Success = 0;

}

namespace LogFetchingTool
{

struct Authentication::Impl
{
    Impl(ISshSession& session, const std::string& userName);
    ~Impl();
    
    std::vector<AuthenticationMethod> 
    parseSupportedAuthentications(const std::string& authentications);

    ISshSession& sshSession;
    const std::string userName;
    std::string fingerPrint;
    bool connectedSession;
};

Authentication::Impl::Impl(ISshSession& session, const std::string& userName) :
    sshSession{session},
    userName{userName}
{
    std::stringstream hostKeyFingerPrint;
    hostKeyFingerPrint << libssh2_hostkey_hash(sshSession, LIBSSH2_HOSTKEY_HASH_SHA1);
    fingerPrint = hostKeyFingerPrint.str();
    for(int i = 0; i < 20; i++)
        std::cout << std::hex << static_cast<short>(fingerPrint[i]) << " ";
    std::cout << std::endl;
}

Authentication::Impl::~Impl()
{
}

std::vector<AuthenticationMethod> 
Authentication::Impl::parseSupportedAuthentications(const std::string& authentications)
{
    auto delimiter = ',';
    std::vector<AuthenticationMethod> authMethods;
    auto commaSeperatedAuthentications = std::regex_replace(authentications,std::regex("\\s+"), "");

    std::stringstream auth{commaSeperatedAuthentications};
    std::string authMethod;
    while(std::getline(auth, authMethod, delimiter))
    {
        if(authenticationMethods.find(authMethod) != authenticationMethods.end())
        {
            authMethods.push_back(authenticationMethods.find(authMethod)->second);
        }
    }
    return authMethods;
}

Authentication::Authentication(ISshSession& session, const std::string& userName) :
    p{std::make_unique<Impl>(session, userName)}
{

}

Authentication::~Authentication() = default;

std::vector<AuthenticationMethod> Authentication::supportedAuthentications()
{
    auto username = p->userName.c_str();

    std::stringstream userAuthList;
    userAuthList << libssh2_userauth_list(p->sshSession, 
        username,
        static_cast<unsigned int>(strlen(username)));
    return p->parseSupportedAuthentications(userAuthList.str());
}

bool Authentication::authenticateWithPassword(const std::string& username, const std::string& pass)
{
    auto supportedAuths = supportedAuthentications();
    bool authenticated = false;
    if(std::find(supportedAuths.begin(), supportedAuths.end(), AuthenticationMethod::Password) != supportedAuths.end()) 
    {
        if(libssh2_userauth_password(p->sshSession, username.c_str(), pass.c_str()) == Success) 
        {
            authenticated = true;
        }
    }
    return authenticated;
}

bool Authentication::authenticateWithPublicKey(
        const std::string& username, 
        const std::string& passPhrase,
        const std::filesystem::path& privateKeyFile,
        const std::filesystem::path& publicKeyFile)
{
    auto supportedAuths = supportedAuthentications();
    bool authenticated = false;
    if(std::find(supportedAuths.begin(), supportedAuths.end(), AuthenticationMethod::Password) != supportedAuths.end()) 
    {
        if(libssh2_userauth_publickey_fromfile(p->sshSession, 
            username.c_str(),
            publicKeyFile == std::filesystem::path() ? nullptr : publicKeyFile.c_str(),
            privateKeyFile.c_str(), 
            passPhrase.c_str()) == Success) 
        {
            authenticated = true;
        }
    }
    return authenticated;
}

}