#include "views/FileListView.h"
#include "ListTreeFactoryMock.h"
#include "ListTreeWidgetMock.h"
#include <gtest/gtest.h>
#include <memory>


namespace TestImLogDetective
{

using namespace ::testing;
using ::testing::StrictMock;
using namespace ImLogDetective;

class TestFileListView : public ::testing::Test {
protected:
    ::testing::InSequence seq;

    TestFileListView();
    ~TestFileListView() = default;

    StrictMock<ListTreeFactoryMock> listTreeFactoryMock;
    ImLogDetective::FileListView fileListView;
};

TestFileListView::TestFileListView() :
    fileListView{listTreeFactoryMock}
{
}

TEST_F(TestFileListView, test_FileListView_draw) {

    const std::vector<std::string>& fileList{"foo", "bar", "lorem", "ipsum"};
    std::unique_ptr<IListTreeWidget> listTreeWidgetMock = std::make_unique<ListTreeWidgetMock>();
    ListTreeWidgetMock* listTreeWidgetMockRef{dynamic_cast<ListTreeWidgetMock*>(listTreeWidgetMock.get())};

    EXPECT_CALL(listTreeFactoryMock, createListTreeWidget()).WillOnce(Return(ByMove(std::move(listTreeWidgetMock))));
    EXPECT_CALL(*listTreeWidgetMockRef, addNode(Eq(fileList[0]), _));
    EXPECT_CALL(*listTreeWidgetMockRef, addNode(Eq(fileList[1]), _));
    EXPECT_CALL(*listTreeWidgetMockRef, addNode(Eq(fileList[2]), _));
    EXPECT_CALL(*listTreeWidgetMockRef, addNode(Eq(fileList[3]), _));
    fileListView.draw(fileList);
}

TEST_F(TestFileListView, test_FileListView_draw_on_empty_fileList) {

    const std::vector<std::string>& fileList{};
    EXPECT_CALL(listTreeFactoryMock, createListTreeWidget()).Times(0);
    fileListView.draw(fileList);
}

}