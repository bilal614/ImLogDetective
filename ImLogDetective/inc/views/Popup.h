
#ifndef IMLOGDETECTIVE_VIEWS_POPUP_H
#define IMLOGDETECTIVE_VIEWS_POPUP_H

#include "views/CopyLogs.h"
#include <string>

struct ImVec2;

namespace ImLogDetective
{

template <typename T>
struct NotCachedPopupInput
{
    T copyLogsInput;
    inline void initInput(const T& input)
    {
        return;
    }
    inline void setInputValue(const std::string& key, const std::string& value)
    {
        return;
    }
    inline std::string getInputValue(const std::string& key)
    {
        return std::string();
    }
    inline const std::vector<std::string> getAllInputs()
    {
        return std::vector<std::string>();
    }
};

template <typename T>
struct CachedCopyLogsPopupInput
{
    T copyLogsInput;
    inline void initInput(const T& input)
    {
        copyLogsInput.getInputRef(CopyLogsDefs::SrcHostPath).insert(0, input.getInputValue(CopyLogsDefs::SrcHostPath));
        copyLogsInput.getInputRef(CopyLogsDefs::DestDir).insert(0, input.getInputValue(CopyLogsDefs::DestDir));
        copyLogsInput.getInputRef(CopyLogsDefs::JumpHost1).insert(0, input.getInputValue(CopyLogsDefs::JumpHost1));
        copyLogsInput.getInputRef(CopyLogsDefs::JumpHost2).insert(0, input.getInputValue(CopyLogsDefs::JumpHost2));
        copyLogsInput.getInputRef(CopyLogsDefs::KeyFilePath1).insert(0, input.getInputValue(CopyLogsDefs::KeyFilePath1));
        copyLogsInput.getInputRef(CopyLogsDefs::KeyFilePath2).insert(0, input.getInputValue(CopyLogsDefs::KeyFilePath2));
    }
    inline void setInputValue(const std::string& key, const std::string& value)
    {
        copyLogsInput.getInputRef(CopyLogsDefs::SrcHostPath).insert(0, value);
    }
    inline std::string& getInputRef(const std::string& key)
    {
        return copyLogsInput.getInputRef(key);
    }
    inline std::string getInputValue(const std::string& key)
    {
        auto input = copyLogsInput.getInputValue(key);
        if(auto pos = input.find('\0'); pos != std::string::npos)
            input.erase(input.find('\0'));
        return input;
    }
    inline const std::vector<std::string> getAllInputs()
    {
        return copyLogsInput.getAllInputs();
    }
};

template <class T, template <class> class CachePolicy>
class Popup : public CachePolicy<T>
{
public:
    ~Popup() = default;
    void open(const ImVec2& popupPosition, const ImVec2& popupSize);
    void draw();
    void close();
    bool isOpen();
    bool okBtnClicked();
    bool closeBtnClicked();
    T getInput();
};

}

#endif