#include "views/WidgetFactoryImpl.h"
#include "dearimgui/TextColor.h"
#include "ImLogDetectiveDefs.h"
#include "MainViewPortMock.h"
#include "ImGuiWidgetWrapperMock.h"
#include "TestUtility.h"
#include <gtest/gtest.h>
#include <memory>


namespace TestImLogDetective
{

using namespace ::testing;
using ::testing::StrictMock;
using namespace ImLogDetective;

class TestWidgetFactoryImpl : public ::testing::Test {
protected:
    ::testing::InSequence seq;

    TestWidgetFactoryImpl();
    ~TestWidgetFactoryImpl() = default;

    const std::string testText;
    StrictMock<MainViewPortMock> mainViewPortMock;
    StrictMock<ImGuiWidgetWrapperMock> imGuiWidgetWrapperMock;
    ImLogDetective::WidgetFactoryImpl widgetFactoryImpl;
};

TestWidgetFactoryImpl::TestWidgetFactoryImpl() :
    testText{"foo bar bla"},
    widgetFactoryImpl{mainViewPortMock, imGuiWidgetWrapperMock}
{
}

TEST_F(TestWidgetFactoryImpl, test_WidgetFactoryImpl_createWindow) {
    ImVec2 windowPosition(0.0f, 0.0f);
    ImVec2 windowSize(12.5f, 10.5f);

    EXPECT_CALL(mainViewPortMock, getViewportPosition()).WillOnce(Return(windowPosition));
    EXPECT_CALL(mainViewPortMock, getAreaSize()).WillOnce(Return(windowSize));

    EXPECT_CALL(imGuiWidgetWrapperMock, setNextWindowPosAndSize(imvec2_equal(windowPosition), imvec2_equal(windowSize)));
    EXPECT_CALL(imGuiWidgetWrapperMock, windowBegin(WindowDefs::ApplicationName, _, _));
    EXPECT_CALL(imGuiWidgetWrapperMock, windowEnd());

    widgetFactoryImpl.createWindow();
}

TEST_F(TestWidgetFactoryImpl, test_WidgetFactoryImpl_createChildWindow) {
    const std::string windowName{"TestWindowName"};
    ImVec2 windowPosition(0.0f, 0.0f);
    ImVec2 windowSize(12.5f, 10.5f);

    EXPECT_CALL(imGuiWidgetWrapperMock, childWindowBegin(windowName, imvec2_equal(windowSize), _));
    EXPECT_CALL(imGuiWidgetWrapperMock, childWindowEnd());

    widgetFactoryImpl.createChildWindow(windowName, windowPosition, windowSize);
}

TEST_F(TestWidgetFactoryImpl, test_WidgetFactoryImpl_createUnformattedText) {
    EXPECT_CALL(imGuiWidgetWrapperMock, textUnformatted(testText));

    widgetFactoryImpl.createUnformattedText(testText);
}

TEST_F(TestWidgetFactoryImpl, test_WidgetFactoryImpl_createTextColored) {
    ImVec4 red(1.0f, 0.0f, 0.0f, 1.0f);
    ImVec4 orange(1.0f, 0.5f, 0.0f, 1.0f);
    ImVec4 yellow(1.0f, 1.0f, 0.0f, 1.0f);
    ImVec4 green(0.0f, 1.0f, 0.0f, 1.0f);
    ImVec4 white(1.0f, 1.0f, 1.0f, 1.0f);

    //Red
    EXPECT_CALL(imGuiWidgetWrapperMock, textColored(imvec4_equal(red), testText));
    widgetFactoryImpl.createTextColored(testText, TextColor::Red);

    //Yellow
    EXPECT_CALL(imGuiWidgetWrapperMock, textColored(imvec4_equal(orange), testText));
    widgetFactoryImpl.createTextColored(testText, TextColor::Orange);

    //Orange
    EXPECT_CALL(imGuiWidgetWrapperMock, textColored(imvec4_equal(yellow), testText));
    widgetFactoryImpl.createTextColored(testText, TextColor::Yellow);

    //Green
    EXPECT_CALL(imGuiWidgetWrapperMock, textColored(imvec4_equal(green), testText));
    widgetFactoryImpl.createTextColored(testText, TextColor::Green);

    //White
    EXPECT_CALL(imGuiWidgetWrapperMock, textColored(imvec4_equal(white), testText));
    widgetFactoryImpl.createTextColored(testText, TextColor::White);
}

TEST_F(TestWidgetFactoryImpl, test_WidgetFactoryImpl_createSelectedTextColored) {
    ImVec4 red(1.0f, 0.0f, 0.0f, 1.0f);
    ImVec4 orange(1.0f, 0.5f, 0.0f, 1.0f);
    ImVec4 yellow(1.0f, 1.0f, 0.0f, 1.0f);
    ImVec4 green(0.0f, 1.0f, 0.0f, 1.0f);
    ImVec4 white(1.0f, 1.0f, 1.0f, 1.0f);

    //Red
    EXPECT_CALL(imGuiWidgetWrapperMock, selectableText(imvec4_equal(red), testText, true));
    widgetFactoryImpl.createSelectedTextColored(testText, TextColor::Red, true);
    EXPECT_CALL(imGuiWidgetWrapperMock, selectableText(imvec4_equal(red), testText, false));
    widgetFactoryImpl.createSelectedTextColored(testText, TextColor::Red, false);

    //Orange
    EXPECT_CALL(imGuiWidgetWrapperMock, selectableText(imvec4_equal(orange), testText, true));
    widgetFactoryImpl.createSelectedTextColored(testText, TextColor::Orange, true);
    EXPECT_CALL(imGuiWidgetWrapperMock, selectableText(imvec4_equal(orange), testText, false));
    widgetFactoryImpl.createSelectedTextColored(testText, TextColor::Orange, false);

    //Yellow
    EXPECT_CALL(imGuiWidgetWrapperMock, textColored(imvec4_equal(yellow), testText));
    widgetFactoryImpl.createSelectedTextColored(testText, TextColor::Yellow, true);
    EXPECT_CALL(imGuiWidgetWrapperMock, textColored(imvec4_equal(yellow), testText));
    widgetFactoryImpl.createSelectedTextColored(testText, TextColor::Yellow, false);

    //Green
    EXPECT_CALL(imGuiWidgetWrapperMock, selectableText(imvec4_equal(green), testText, true));
    widgetFactoryImpl.createSelectedTextColored(testText, TextColor::Green, true);
    EXPECT_CALL(imGuiWidgetWrapperMock, selectableText(imvec4_equal(green), testText, false));
    widgetFactoryImpl.createSelectedTextColored(testText, TextColor::Green, false);

    //White
    EXPECT_CALL(imGuiWidgetWrapperMock, selectableText(imvec4_equal(white), testText, true));
    widgetFactoryImpl.createSelectedTextColored(testText, TextColor::White, true);
    EXPECT_CALL(imGuiWidgetWrapperMock, selectableText(imvec4_equal(white), testText, false));
    widgetFactoryImpl.createSelectedTextColored(testText, TextColor::White, false);

}


TEST_F(TestWidgetFactoryImpl, test_WidgetFactoryImpl_open_popup_and_set_a_layout_then_close) {
    const std::string popupWindowName{"TestPopupWindowName"};
    ImVec2 popupPosition(0.0f, 0.0f);
    ImVec2 popupSize(12.5f, 10.5f);
    PopupButton ok{"Okay"}, close{"Close"}, help{"Help"};
    std::vector<PopupButton> buttonGroup{ok, close, help};
    std::vector<std::string> textBoxGroupInputs{4};
    auto textBoxGroupWidth = 2.0f;
    PopupInputTextBox input1{"Input 1", textBoxGroupInputs[0], textBoxGroupWidth}, 
        input2{"Input 1", textBoxGroupInputs[1], textBoxGroupWidth}, 
        input3{"Input 3", textBoxGroupInputs[2], textBoxGroupWidth};
    std::vector<PopupInputTextBox> popupInputTextBoxGroup{input1, input2, input3};
    ImVec4 red(1.0f, 0.0f, 0.0f, 1.0f);

    EXPECT_CALL(imGuiWidgetWrapperMock, openPopup(popupWindowName));
    EXPECT_CALL(imGuiWidgetWrapperMock, setNextWindowPos(imvec2_equal(popupPosition)));
    EXPECT_CALL(imGuiWidgetWrapperMock, setNextWindowSize(imvec2_equal(popupSize)));
    widgetFactoryImpl.open(popupPosition, popupSize, popupWindowName);

    EXPECT_TRUE(widgetFactoryImpl.isPopupOpen());

    EXPECT_CALL(imGuiWidgetWrapperMock, beginPopupModal(popupWindowName)).WillOnce(Return(true));
    widgetFactoryImpl.beginLayout(popupWindowName);

    EXPECT_CALL(imGuiWidgetWrapperMock, button(ok.name));
    widgetFactoryImpl.createButton(ok);

    EXPECT_CALL(imGuiWidgetWrapperMock, button(ok.name));
    EXPECT_CALL(imGuiWidgetWrapperMock, sameLine());
    EXPECT_CALL(imGuiWidgetWrapperMock, button(close.name));
    EXPECT_CALL(imGuiWidgetWrapperMock, sameLine());
    EXPECT_CALL(imGuiWidgetWrapperMock, button(help.name));
    widgetFactoryImpl.createButtonGroup(buttonGroup);

    EXPECT_CALL(imGuiWidgetWrapperMock, pushItemWidth(input1.width));
    EXPECT_CALL(imGuiWidgetWrapperMock, inputText(input1.name, input1.input.data(), input1.width));
    EXPECT_CALL(imGuiWidgetWrapperMock, popItemWidth());
    widgetFactoryImpl.createInputTextBox(input1.name, input1.input, input1.width);


    auto protectedTextBoxLabel{"Protected Text Box Label"};
    std::string protectedTextBoxInput;
    float protectedTextBoxWidth = 3.0f;
    EXPECT_CALL(imGuiWidgetWrapperMock, pushItemWidth(protectedTextBoxWidth));
    EXPECT_CALL(imGuiWidgetWrapperMock, inputPassword(protectedTextBoxLabel, protectedTextBoxInput.data(), protectedTextBoxWidth));
    EXPECT_CALL(imGuiWidgetWrapperMock, popItemWidth());
    widgetFactoryImpl.createProtectedInputTextBox(protectedTextBoxLabel, protectedTextBoxInput, protectedTextBoxWidth);

    auto inpuTextBoxGroupTitle = "Input Text Box Group";
    EXPECT_CALL(imGuiWidgetWrapperMock, textUnformatted(inpuTextBoxGroupTitle));
    EXPECT_CALL(imGuiWidgetWrapperMock, pushItemWidth(input1.width));
    EXPECT_CALL(imGuiWidgetWrapperMock, inputText(input1.name, input1.input.data(), input1.width));
    EXPECT_CALL(imGuiWidgetWrapperMock, popItemWidth());
    EXPECT_CALL(imGuiWidgetWrapperMock, sameLine());
    EXPECT_CALL(imGuiWidgetWrapperMock, pushItemWidth(input2.width));
    EXPECT_CALL(imGuiWidgetWrapperMock, inputText(input2.name, input2.input.data(), input2.width));
    EXPECT_CALL(imGuiWidgetWrapperMock, popItemWidth());
    EXPECT_CALL(imGuiWidgetWrapperMock, sameLine());
    EXPECT_CALL(imGuiWidgetWrapperMock, pushItemWidth(input3.width));
    EXPECT_CALL(imGuiWidgetWrapperMock, inputText(input3.name, input3.input.data(), input3.width));
    EXPECT_CALL(imGuiWidgetWrapperMock, popItemWidth());
    widgetFactoryImpl.createInputTextBoxGroup(popupInputTextBoxGroup, inpuTextBoxGroupTitle, true, false);

    auto collapsableInpuTextBoxGroupTitle = "Collapsable Input Text Box Group";
    EXPECT_CALL(imGuiWidgetWrapperMock, collapsingHeader(collapsableInpuTextBoxGroupTitle)).WillOnce(Return(true));
    EXPECT_CALL(imGuiWidgetWrapperMock, pushItemWidth(input1.width));
    EXPECT_CALL(imGuiWidgetWrapperMock, inputText(input1.name, input1.input.data(), input1.width));
    EXPECT_CALL(imGuiWidgetWrapperMock, popItemWidth());
    EXPECT_CALL(imGuiWidgetWrapperMock, sameLine());
    EXPECT_CALL(imGuiWidgetWrapperMock, pushItemWidth(input2.width));
    EXPECT_CALL(imGuiWidgetWrapperMock, inputText(input2.name, input2.input.data(), input2.width));
    EXPECT_CALL(imGuiWidgetWrapperMock, popItemWidth());
    EXPECT_CALL(imGuiWidgetWrapperMock, sameLine());
    EXPECT_CALL(imGuiWidgetWrapperMock, pushItemWidth(input3.width));
    EXPECT_CALL(imGuiWidgetWrapperMock, inputText(input3.name, input3.input.data(), input3.width));
    EXPECT_CALL(imGuiWidgetWrapperMock, popItemWidth());
    widgetFactoryImpl.createInputTextBoxGroup(popupInputTextBoxGroup, collapsableInpuTextBoxGroupTitle, true, true);

    auto errorText = "Test error text";
    EXPECT_CALL(imGuiWidgetWrapperMock, textColored(imvec4_equal(red), errorText));
    widgetFactoryImpl.showErrorText(errorText);

    EXPECT_CALL(imGuiWidgetWrapperMock, endPopup());
    widgetFactoryImpl.endLayout();

    EXPECT_CALL(imGuiWidgetWrapperMock, closeCurrentPopup());
    widgetFactoryImpl.close();
    EXPECT_FALSE(widgetFactoryImpl.isPopupOpen());
}

}