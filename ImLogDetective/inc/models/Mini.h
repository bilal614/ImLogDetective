
#ifndef IMLOGDETECTIVE_MODELS_MINI_H
#define IMLOGDETECTIVE_MODELS_MINI_H

#include <filesystem>

namespace ImLogDetective
{

class Mini 
{
public:
    virtual~Mini() = default;
    virtual void set(const std::string& section, const std::string& name, const std::string& value) = 0;
    virtual std::string get(const std::string& section, const std::string& name) const = 0;
    virtual bool updateIniFile() = 0;
};

}

#endif