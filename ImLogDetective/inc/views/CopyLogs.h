
#ifndef IMLOGDETECTIVE_VIEWS_COPYLOGS_H
#define IMLOGDETECTIVE_VIEWS_COPYLOGS_H

#include "views/Popup.h"
#include "ImLogDetectiveDefs.h"
#include <algorithm>
#include <filesystem>
#include <map>
#include <utility>
#include <vector>

struct ImVec2;

namespace ImLogDetective
{

struct CopyLogs{
    CopyLogs() :
        popInputs{
            {CopyLogsDefs::SrcHostPath, std::string(1024, '\0')},
            {CopyLogsDefs::DestDir, std::string(1024, '\0')},
            {CopyLogsDefs::JumpHost1, std::string(1024, '\0')},
            {CopyLogsDefs::JumpHost2, std::string(1024, '\0')},
            {CopyLogsDefs::KeyFilePath1, std::string(1024, '\0')},
            {CopyLogsDefs::KeyFilePath2, std::string(1024, '\0')},
        }
    {}
    std::map<std::string, std::string> popInputs;
    inline std::string& getInputRef(const std::string& key)
    {
        if(popInputs.find(key) != popInputs.end())
        {
            return popInputs[key];
        }
        throw std::exception();
    }

    inline std::string getInputValue(const std::string& key) const
    {
        if(popInputs.find(key) != popInputs.end())
        {
            return popInputs.find(key)->second;
        }
        throw std::exception();
    }

    inline const std::vector<std::string> getAllInputs()
    {
        std::vector<std::string> inputValues;
        std::transform( 
            popInputs.begin(), 
            popInputs.end(),
            std::back_inserter(inputValues),
            [](auto &kv){ return kv.second;} 
        );
        return inputValues;
    }
};

}

#endif