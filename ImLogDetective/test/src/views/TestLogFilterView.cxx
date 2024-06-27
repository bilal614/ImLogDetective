#include "views/LogFilterView.h"
#include "ImLogDetectiveDefs.h"
#include "ImGuiTextFilterWrapperMock.h"
#include "ImGuiWidgetWrapperMock.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <tuple>

namespace TestImLogDetective
{

using namespace ::testing;
using ::testing::StrictMock;
using namespace ImLogDetective;

class TestLogFilterView : public ::testing::TestWithParam<std::tuple<bool, bool, bool, bool>> {
protected:
    ::testing::InSequence seq;

    TestLogFilterView();
    ~TestLogFilterView() = default;

    StrictMock<ImGuiTextFilterWrapperMock> imGuiTextFilterWrapperMock;
    StrictMock<ImGuiWidgetWrapperMock> imGuiWidgetWrapperMock;
    ImLogDetective::LogFilterView logFilterView;
};

TestLogFilterView::TestLogFilterView() :
    logFilterView{imGuiTextFilterWrapperMock, imGuiWidgetWrapperMock}
{
}

TEST_P(TestLogFilterView, test_LogFilterView_drawFilterCheckBoxes) {

    auto params = GetParam();
    bool debugChecked = std::get<0>(params);
    bool infoChecked = std::get<1>(params);
    bool warningChecked = std::get<2>(params);
    bool errorChecked = std::get<3>(params);

    EXPECT_CALL(imGuiWidgetWrapperMock, sameLine());
    EXPECT_CALL(imGuiWidgetWrapperMock, checkBox(Eq(ImLogDetective::LogFilterDefs::DebugCheckBoxLabel), _))
        .WillOnce(DoAll(::testing::SetArgReferee<1>(debugChecked), Return(true)));
    EXPECT_CALL(imGuiWidgetWrapperMock, sameLine());
    EXPECT_CALL(imGuiWidgetWrapperMock, checkBox(Eq(ImLogDetective::LogFilterDefs::InfoCheckBoxLabel), _))
        .WillOnce(DoAll(::testing::SetArgReferee<1>(infoChecked), Return(true)));
    EXPECT_CALL(imGuiWidgetWrapperMock, sameLine());
    EXPECT_CALL(imGuiWidgetWrapperMock, checkBox(Eq(ImLogDetective::LogFilterDefs::WarningCheckBoxLabel), _))
        .WillOnce(DoAll(::testing::SetArgReferee<1>(warningChecked), Return(true)));
    EXPECT_CALL(imGuiWidgetWrapperMock, sameLine());
    EXPECT_CALL(imGuiWidgetWrapperMock, checkBox(Eq(ImLogDetective::LogFilterDefs::ErrorCheckBoxLabel), _))
        .WillOnce(DoAll(::testing::SetArgReferee<1>(errorChecked), Return(true)));
    EXPECT_CALL(imGuiWidgetWrapperMock, separator());
    EXPECT_CALL(imGuiTextFilterWrapperMock, draw());
    logFilterView.drawFilterCheckBoxes();

    EXPECT_EQ(logFilterView.getDebugChecked(), debugChecked);
    EXPECT_EQ(logFilterView.getInfoChecked(), infoChecked);
    EXPECT_EQ(logFilterView.getWarningChecked(), warningChecked);
    EXPECT_EQ(logFilterView.getErrorChecked(), errorChecked);
}

INSTANTIATE_TEST_CASE_P(
    LogFilterViewTests,
    TestLogFilterView,
    ::testing::Values(
        std::tuple{true, true, true, true},
        std::tuple{false, true, true, true},
        std::tuple{false, false, true, true},
        std::tuple{true, false, false, true},
        std::tuple{false, false, false, true},
        std::tuple{false, false, false, false}
    ));
}