
#ifndef IMLOGDETECTIVE_MODELS_MINIIMPL_H
#define IMLOGDETECTIVE_MODELS_MINIIMPL_H

#include "models/Mini.h"
#include <memory>

namespace ImLogDetective
{

class MiniImpl : public Mini
{
public:
    MiniImpl(const std::filesystem::path& iniFilePath);
    ~MiniImpl();
    void set(const std::string& section, const std::string& name, const std::string& value) final;
    std::string get(const std::string& section, const std::string& name) const final;
    bool updateIniFile() final;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}

#endif