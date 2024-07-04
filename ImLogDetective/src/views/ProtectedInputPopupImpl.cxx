
#include "views/ProtectedInputPopupImpl.h"
#include "views/ModalPopupFactory.h"
#include <memory>
#include <string>
#include <unordered_map>
#include "imgui.h"
#include "ImLogDetectiveDefs.h"

struct ImVec2;

namespace ImLogDetective
{

struct ProtectedInputPopupImpl::Impl
{
    Impl(ModalPopupFactory& modalPopupFactory);
    ~Impl() = default;

    ModalPopupFactory& modalPopupFactory;

    bool okClicked;
    bool closeClicked;
    bool opened;
    std::string prompt;
    std::unordered_map<int, std::string> passMapp; //TODO put pass in map

    std::string passInput;
};

ProtectedInputPopupImpl::Impl::Impl(ModalPopupFactory& modalPopupFactory) :
    okClicked{false},
    closeClicked{false},
    opened{false},
    modalPopupFactory{modalPopupFactory},
    passInput(1024, '\0')
{

}

ProtectedInputPopupImpl::ProtectedInputPopupImpl(ModalPopupFactory& modalPopupFactory) :
    p{std::make_unique<Impl>(modalPopupFactory)}
{
}

ProtectedInputPopupImpl::~ProtectedInputPopupImpl() = default;

void ProtectedInputPopupImpl::open(const ImVec2& popupPosition, const ImVec2& popupSize)
{
    p->modalPopupFactory.open(popupPosition, popupSize, ProtectedInputDefs::Name);
    if(!p->opened)
    {
        p->passInput = std::string(1024, '\0');
        p->opened = true;
    }
}

void ProtectedInputPopupImpl::setPrompt(const std::string& prompt)
{
    p->prompt = ProtectedInputDefs::Prompt + prompt;
}

void ProtectedInputPopupImpl::draw()
{
    if(p->opened)
    {
        p->modalPopupFactory.beginLayout(ProtectedInputDefs::Name);
        p->modalPopupFactory.createProtectedInputTextBox(p->prompt, p->passInput, ProtectedInputDefs::TextBoxWidth);
        std::vector<PopupButton> popupButtons{
            PopupButton{Common::OkBtn},
            PopupButton{Common::CloseBtn}};
        p->modalPopupFactory.createButtonGroup(popupButtons);

        //TODO Implement input validation, in presenter
        {
            //update state from UI elements
            p->okClicked = popupButtons[0].clicked;
            p->closeClicked = popupButtons[1].clicked;
        }

        p->modalPopupFactory.endLayout();
    }
}

void ProtectedInputPopupImpl::close()
{
    p->passInput = std::string(1024, '\0');
    p->okClicked = false;
    p->closeClicked = false;
    p->opened = false;
    p->modalPopupFactory.close();
}

bool ProtectedInputPopupImpl::isOpen()
{
    return p->modalPopupFactory.isPopupOpen() && p->opened;
}

bool ProtectedInputPopupImpl::okBtnClicked()
{
    return p->okClicked;
}

bool ProtectedInputPopupImpl::closeBtnClicked()
{
    return p->closeClicked;
}

std::string ProtectedInputPopupImpl::getInput()
{
    p->passInput.erase(p->passInput.find('\0'));
    return p->passInput;
}

}