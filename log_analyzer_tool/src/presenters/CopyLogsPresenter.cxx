#include <memory>
#include "imgui.h"
#include "log_scp_wrapper/IAuthenticationWorkFlow.h"
#include "log_scp_wrapper/IScpExecutor.h"
#include "presenters/CopyLogsPresenter.h"
#include "views/ICopyLogsPopup.h"
#include "views/IProtectedInputPopup.h"
#include "LogAnalyzerToolDefs.h"

#include <map>
#include "views/IPopup.h"

//REMOVE LATER
#include <iostream>
#include <thread>

namespace LogAnalyzerTool
{

enum class PopupType {
    COPY_LOGS,
    KEY_FILE_AUTHENTICATION,
    USER_AUTHENTICATION
};


struct PopupState{
    bool open_;
    PopupType type;
    PopupState(PopupType type) :
        type{},
        open_{false}
    {
    }
    void open()
    {
        open_ = true;
    }
    void close()
    {
        open_ = false;
    }

    bool operator<(const PopupState& t) const
    {
        return (this->type < t.type);
    }

};

struct PopupManager{
     PopupManager() :
            popups{
                {PopupType::COPY_LOGS, PopupState{PopupType::COPY_LOGS}}, 
                {PopupType::KEY_FILE_AUTHENTICATION, PopupState{PopupType::KEY_FILE_AUTHENTICATION}},
                {PopupType::USER_AUTHENTICATION, PopupState{PopupType::USER_AUTHENTICATION}}
            }
    {
    }

    std::map<PopupType, PopupState> popups;

    bool openPopup(PopupType type)
    {
        if(popups.find(type) == popups.end())
        {
            return false;
        }
        auto anyPopupOpen = std::any_of(popups.begin(), popups.end(), [](const auto& p){ return p.second.open_;});
        if(anyPopupOpen)
        {
            return false;
        }
        if(popups.find(type) != popups.end())
        {
            auto found = popups.find(type);
            found->second.open();
            return true;
        }
        return false;
    }

    bool closePopup(PopupType type)
    {
        if(popups.find(type) != popups.end())
        {
            auto found = popups.find(type);
            found->second.close();
            return true;
        }
        return false;
    }
};

struct CopyLogsPresenter::Impl
{
    Impl(ICopyLogsPopup& copyPopupLogs,
        IProtectedInputPopup& protectedInputPopup,
        LogScpWrapper::IScpExecutor& scpExecutor);
    ~Impl() = default;

    void processPopupInput();
    void cleanInput(std::string& input);

    ICopyLogsPopup& copyPopupLogs;
    IProtectedInputPopup& protectedInputPopup;
    LogScpWrapper::IScpExecutor& scpExecutor;
    bool downloadInit;
    bool isClosed;
    bool passPopup;
    //PopupManager popupManager;
};

CopyLogsPresenter::Impl::Impl(ICopyLogsPopup& copyPopupLogs,
    IProtectedInputPopup& protectedInputPopup,
    LogScpWrapper::IScpExecutor& scpExecutor) :
        copyPopupLogs{copyPopupLogs},
        protectedInputPopup{protectedInputPopup},
        scpExecutor{scpExecutor},
        downloadInit{false},
        isClosed{true},
        passPopup{false}
        //popupManager{}
{
}

void CopyLogsPresenter::Impl::cleanInput(std::string& input)
{
    input.erase(input.find('\0'));
}
void CopyLogsPresenter::Impl::processPopupInput()
{
    if (copyPopupLogs.closeBtnClicked())
    {
        std::cout << "CLOSE BTN CLICKED" << std::endl;
        // if(popupManager.closePopup(PopupType::COPY_LOGS))
        // {
            isClosed = true;
            copyPopupLogs.close();
        // }
        return;
    }
    if(copyPopupLogs.okBtnClicked())
    {
        std::cout << "COPY BTN CLICKED" << std::endl;
        if(!downloadInit)
        {
            auto input = copyPopupLogs.getInput();
            if(input.srcHostPath.find_first_not_of('\0') != std::string::npos)
            {
                cleanInput(input.srcHostPath);
                scpExecutor.setSourceRemoteHostPath(input.srcHostPath);
            }
            if(input.dstDirectory.find_first_not_of('\0') != std::string::npos)
            {
                cleanInput(input.dstDirectory);
                scpExecutor.setDestinationLocalPath(input.dstDirectory);
            }
            if(input.jumpHostPath1.find_first_not_of('\0') != std::string::npos)
            {
                cleanInput(input.jumpHostPath1);
                scpExecutor.addJumpHost(input.jumpHostPath1);
            }
            if(input.jumpHostPath2.find_first_not_of('\0') != std::string::npos)
            {
                cleanInput(input.jumpHostPath2);
                scpExecutor.addJumpHost(input.jumpHostPath2);
            }
            if(input.keyFile1.find_first_not_of('\0') != std::string::npos)
            {
                cleanInput(input.keyFile1);
                scpExecutor.addIdentityFile(input.keyFile1);
            }
            if(input.keyFile2.find_first_not_of('\0') != std::string::npos)
            {
                cleanInput(input.keyFile2);
                scpExecutor.addIdentityFile(input.keyFile2);
            }
            scpExecutor.download();
            downloadInit = true;
        }
        // if(popupManager.closePopup(PopupType::COPY_LOGS))
        // {
            isClosed = true;
            copyPopupLogs.close();
        // }
        return;
    }

}

CopyLogsPresenter::CopyLogsPresenter(ICopyLogsPopup& copyPopupLogs, 
    IProtectedInputPopup& protectedInputPopup,
    LogScpWrapper::IScpExecutor& scpExecutor) :
        p{std::make_unique<Impl>(copyPopupLogs, protectedInputPopup, scpExecutor)}
{
}

CopyLogsPresenter::~CopyLogsPresenter() = default;

void CopyLogsPresenter::update(bool openPopup, const ImVec2& popupPosition, const ImVec2& popupSize)
{

    if(openPopup)
    {
        p->isClosed = false;
        p->copyPopupLogs.open(popupPosition, popupSize);

        p->copyPopupLogs.draw();
        p->processPopupInput();
    }

    if(p->passPopup)
    {
        //TODO Change hard-coded position coordinates 
        p->protectedInputPopup.open(ImVec2{300, 300}, ImVec2{ProtectedInputDefs::PopupWidth, ProtectedInputDefs::PopupHeight});
        if(p->protectedInputPopup.isOpen())
        {
            p->protectedInputPopup.draw();
            if(p->protectedInputPopup.okBtnClicked())
            {
                auto pass = p->protectedInputPopup.getInput();
                p->scpExecutor.enterPass(pass);
                p->protectedInputPopup.close();
                p->passPopup = false;
            }
            if(p->protectedInputPopup.closeBtnClicked())
            {
                p->passPopup = false;
                p->protectedInputPopup.close();
            }
        }
    }
}

void CopyLogsPresenter::monitorCopyLogs()
{
    if(p->downloadInit && p->scpExecutor.downloadFinished())
    {
        p->downloadInit = false;
    }

    if(p->downloadInit && !p->scpExecutor.downloadStarted())
    {
        auto request = p->scpExecutor.getAuthenticationRequest();

        if(request.prompt == LogScpWrapper::PromptType::HostAuthenticity)
        {
            std::cout << "Entering HostAuthenticity, " << p->scpExecutor.prompt() << std::endl;
            p->scpExecutor.enterPass("yes");
        }
        if(request.prompt == LogScpWrapper::PromptType::KeyFileAuthentication)
        {
            std::cout << "Entering KeyFileAuthentication, " << p->scpExecutor.prompt() << std::endl;
            p->passPopup = true;
        }
        if(request.prompt == LogScpWrapper::PromptType::UserAuthentication)
        {
            std::cout << "Entering UserAuthentication, " << p->scpExecutor.prompt() << std::endl;
            p->passPopup = true;
        }
    }

    if(p->scpExecutor.downloadFinished())
    {
        // p->isClosed = true;
        // p->copyPopupLogs.close();
    }
}

bool CopyLogsPresenter::isClosed()
{
    return p->isClosed;
}

}