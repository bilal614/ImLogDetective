
#include "models/Mini.h"
#include "mini/ini.h"

namespace ImLogDetective
{

struct Mini::Impl
{
    Impl(const std::filesystem::path& iniFilePath);
    ~Impl() = default;

    mINI::INIFile iniFile;
    mINI::INIStructure ini;
};

Mini::Impl::Impl(const std::filesystem::path& iniFilePath) :
    iniFile{iniFilePath.string()},
    ini{}
{
    iniFile.read(ini);
}

Mini::Mini(const std::filesystem::path& iniFilePath) :
    p{std::make_unique<Impl>(iniFilePath)}
{
}

Mini::~Mini() = default;

void Mini::set(const std::string& section, const std::string& name, const std::string& value)
{
    p->ini[section][name] = value;
}

std::string Mini::get(const std::string& section, const std::string& name)
{
    return p->ini[section][name];
}

void Mini::updateIniFile()
{
    p->iniFile.write(p->ini);
}

}