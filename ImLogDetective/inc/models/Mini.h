#pragma once

#include "IMini.h"
#include <memory>

namespace ImLogDetective
{

class Mini : public IMini
{
public:
    Mini(const std::filesystem::path& iniFilePath);
    ~Mini();
    void set(const std::string& section, const std::string& name, const std::string& value) final;
    std::string get(const std::string& section, const std::string& name) final;
    void updateIniFile() final;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}