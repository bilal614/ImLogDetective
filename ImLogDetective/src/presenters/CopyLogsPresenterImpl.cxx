#include "presenters/CopyLogsPresenterImpl.h"
#include "ScpWrapper/IAuthenticationWorkFlow.h"
#include "ScpWrapper/IScpExecutor.h"
#include "models/Mini.h"
#include "views/ProtectedInputPopupImpl.h"
#include "views/CopyLogsPopupImpl.h"
#include "ImLogDetectiveDefs.h"
#include "imgui.h"
#include "views/Popup.h"
#include <algorithm>
#include <map>
#include <memory>


namespace ImLogDetective
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

struct CopyLogsPresenterImpl::Impl
{
    Impl(CopyLogsPopupImpl& copyPopupLogs,
        ProtectedInputPopupImpl& protectedInputPopup,
        ImLogDetective::IScpExecutor& scpExecutor,
        Mini& mini);
    ~Impl() = default;

    void processPopupInput();
    void cleanInput(std::string& input);

    CopyLogsPopupImpl& copyPopupLogs;
    ProtectedInputPopupImpl& protectedInputPopup;
    ImLogDetective::IScpExecutor& scpExecutor;
    Mini& mini;
    bool downloadInit;
    bool isClosed;
    bool passPopup;
    //PopupManager popupManager;
};

CopyLogsPresenterImpl::Impl::Impl(CopyLogsPopupImpl& copyPopupLogs,
    ProtectedInputPopupImpl& protectedInputPopup,
    ImLogDetective::IScpExecutor& scpExecutor,
    Mini& mini) :
        copyPopupLogs{copyPopupLogs},
        protectedInputPopup{protectedInputPopup},
        scpExecutor{scpExecutor},
        downloadInit{false},
        isClosed{true},
        passPopup{false},
        mini{mini}
        //popupManager{}
{
}

void CopyLogsPresenterImpl::Impl::processPopupInput()
{
    if (copyPopupLogs.closeBtnClicked())
    {
        // if(popupManager.closePopup(PopupType::COPY_LOGS))
        // {
            mini.updateIniFile();
            isClosed = true;
            copyPopupLogs.close();
        // }
        return;
    }
    if(copyPopupLogs.okBtnClicked())
    {
        if(!downloadInit)
        {
            if(auto srcHostPath = copyPopupLogs.getInputValue(CopyLogsDefs::SrcHostPath); !srcHostPath.empty())
            {
                mini.set(IniDefs::CopyLogsSection::Name, 
                    IniDefs::CopyLogsSection::SrcHostPath, 
                    srcHostPath);
                scpExecutor.setSourceRemoteHostPath(srcHostPath);
            }
            if(auto dstDirectory = copyPopupLogs.getInputValue(CopyLogsDefs::DestDir); !dstDirectory.empty())
            {
                mini.set(IniDefs::CopyLogsSection::Name, 
                    IniDefs::CopyLogsSection::DestinationPath, 
                    dstDirectory);
                scpExecutor.setDestinationLocalPath(dstDirectory);
            }
            if(auto jumpHostPath1 = copyPopupLogs.getInputValue(CopyLogsDefs::JumpHost1); !jumpHostPath1.empty())
            {
                mini.set(IniDefs::CopyLogsSection::Name, 
                    IniDefs::CopyLogsSection::JumpHost1, 
                    jumpHostPath1);
                scpExecutor.addJumpHost(jumpHostPath1);
            }
            if(auto jumpHostPath2 = copyPopupLogs.getInputValue(CopyLogsDefs::JumpHost2); !jumpHostPath2.empty())
            {
                mini.set(IniDefs::CopyLogsSection::Name, 
                    IniDefs::CopyLogsSection::JumpHost2, 
                    jumpHostPath2);
                scpExecutor.addJumpHost(jumpHostPath2);
            }
            
            if(auto keyFile1 = copyPopupLogs.getInputValue(CopyLogsDefs::KeyFilePath1); !keyFile1.empty())
            {
                mini.set(IniDefs::CopyLogsSection::Name, 
                    IniDefs::CopyLogsSection::KeyFilePath1, 
                    keyFile1);
                scpExecutor.addIdentityFile(keyFile1);
            }
            if(auto keyFile2 = copyPopupLogs.getInputValue(CopyLogsDefs::KeyFilePath2); !keyFile2.empty())
            {
                mini.set(IniDefs::CopyLogsSection::Name, 
                    IniDefs::CopyLogsSection::KeyFilePath2, 
                    keyFile2);
                scpExecutor.addIdentityFile(keyFile2);
            }
            scpExecutor.download();
            downloadInit = true;
        }
        // if(popupManager.closePopup(PopupType::COPY_LOGS))
        // {
            mini.updateIniFile();
            isClosed = true;
            copyPopupLogs.close();
        // }
        return;
    }
}

CopyLogsPresenterImpl::CopyLogsPresenterImpl(CopyLogsPopupImpl& copyPopupLogs, 
    ProtectedInputPopupImpl& protectedInputPopup,
    ImLogDetective::IScpExecutor& scpExecutor,
    Mini& mini) :
        p{std::make_unique<Impl>(copyPopupLogs, protectedInputPopup, scpExecutor, mini)}
{
}

CopyLogsPresenterImpl::~CopyLogsPresenterImpl() = default;

void CopyLogsPresenterImpl::update(bool openPopup, const ImVec2& popupPosition, const ImVec2& popupSize)
{
    if(openPopup)
    {
        if(p->isClosed)
        {
            CopyLogs initialCopyLogs;
            initialCopyLogs.getInputRef(CopyLogsDefs::SrcHostPath)  =   p->mini.get(IniDefs::CopyLogsSection::Name, IniDefs::CopyLogsSection::SrcHostPath);
            initialCopyLogs.getInputRef(CopyLogsDefs::DestDir)      =   p->mini.get(IniDefs::CopyLogsSection::Name, IniDefs::CopyLogsSection::DestinationPath);
            initialCopyLogs.getInputRef(CopyLogsDefs::JumpHost1)    =   p->mini.get(IniDefs::CopyLogsSection::Name, IniDefs::CopyLogsSection::JumpHost1);
            initialCopyLogs.getInputRef(CopyLogsDefs::JumpHost2)    =   p->mini.get(IniDefs::CopyLogsSection::Name, IniDefs::CopyLogsSection::JumpHost2);
            initialCopyLogs.getInputRef(CopyLogsDefs::KeyFilePath1) =   p->mini.get(IniDefs::CopyLogsSection::Name, IniDefs::CopyLogsSection::KeyFilePath1);
            initialCopyLogs.getInputRef(CopyLogsDefs::KeyFilePath2) =   p->mini.get(IniDefs::CopyLogsSection::Name, IniDefs::CopyLogsSection::KeyFilePath2);
            p->copyPopupLogs.initInput(initialCopyLogs);
        }
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
            p->protectedInputPopup.setPrompt(p->scpExecutor.prompt());
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

void CopyLogsPresenterImpl::monitorCopyLogs()
{
    if(p->downloadInit && !p->scpExecutor.downloadStarted())
    {
        auto request = p->scpExecutor.getAuthenticationRequest();

        if(request.prompt == ImLogDetective::PromptType::HostAuthenticity)
        {
            p->scpExecutor.enterPass("yes");
        }
        if(request.prompt == ImLogDetective::PromptType::KeyFileAuthentication)
        {
            p->passPopup = true;
        }
        if(request.prompt == ImLogDetective::PromptType::UserAuthentication)
        {
            p->passPopup = true;
        }
    }

    if(p->scpExecutor.downloadFinished())
    {
        p->downloadInit = false;
    }
}

bool CopyLogsPresenterImpl::isClosed()
{
    return p->isClosed;
}

}