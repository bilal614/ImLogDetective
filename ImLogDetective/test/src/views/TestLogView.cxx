#include "views/LogViewImpl.h"
#include "TextWidgetFactoryMock.h"
#include "models/LogLine.h"
#include <gtest/gtest.h>

namespace TestImLogDetective
{

using namespace ::testing;
using ::testing::StrictMock;
using namespace ImLogDetective;

class TestLogView : public ::testing::Test {
protected:
    ::testing::InSequence seq;

    TestLogView();
    ~TestLogView() = default;

    StrictMock<TextWidgetFactoryMock> textWidgetFactoryMock;
    ImLogDetective::LogViewImpl logView;
};

TestLogView::TestLogView() :
    logView{textWidgetFactoryMock}
{
}

TEST_F(TestLogView, test_TestLogView_drawLogLineText_draws_log_line_with_correct_color_scheme) {

    auto expLogLineText = "foo-bar";
    auto expLogLineColor = ImLogDetective::TextColor::Yellow;
    ImLogDetective::LogLine logLineUnknown{expLogLineText, ImLogDetective::LogLevel::Unknown};
    EXPECT_CALL(textWidgetFactoryMock, createSelectedTextColored(Eq(expLogLineText), Eq(expLogLineColor), false));
    logView.drawLogLineText(logLineUnknown);

    expLogLineText = "dolore magnam";
    expLogLineColor = ImLogDetective::TextColor::White;
    ImLogDetective::LogLine logLineDebug{expLogLineText, ImLogDetective::LogLevel::Debug};
    EXPECT_CALL(textWidgetFactoryMock, createSelectedTextColored(Eq(expLogLineText), Eq(expLogLineColor), false));
    logView.drawLogLineText(logLineDebug);

    expLogLineText = "bar-foo";
    expLogLineColor = ImLogDetective::TextColor::White;
    ImLogDetective::LogLine logLineInfo{expLogLineText, ImLogDetective::LogLevel::Info};
    EXPECT_CALL(textWidgetFactoryMock, createSelectedTextColored(Eq(expLogLineText), Eq(expLogLineColor), false));
    logView.drawLogLineText(logLineInfo);

    expLogLineText = "lorem ipsum";
    expLogLineColor = ImLogDetective::TextColor::Orange;
    ImLogDetective::LogLine logLineWarning{expLogLineText, ImLogDetective::LogLevel::Warning};
    EXPECT_CALL(textWidgetFactoryMock, createSelectedTextColored(Eq(expLogLineText), Eq(expLogLineColor), false));
    logView.drawLogLineText(logLineWarning);

    expLogLineText = "eiusmod tempor";
    expLogLineColor = ImLogDetective::TextColor::Red;
    ImLogDetective::LogLine logLineError{expLogLineText, ImLogDetective::LogLevel::Error};
    EXPECT_CALL(textWidgetFactoryMock, createSelectedTextColored(Eq(expLogLineText), Eq(expLogLineColor), false));
    logView.drawLogLineText(logLineError);
}

}