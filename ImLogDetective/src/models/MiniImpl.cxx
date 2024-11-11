
#include "models/MiniImpl.h"
#include "mini/ini.h"

namespace ImLogDetective
{

struct MiniImpl::Impl
{
    Impl(const std::filesystem::path& iniFilePath);
    ~Impl() = default;

    mINI::INIFile iniFile;
    mINI::INIStructure ini;
};

MiniImpl::Impl::Impl(const std::filesystem::path& iniFilePath) :
    iniFile{iniFilePath.string()},
    ini{}
{
    iniFile.read(ini);
}

MiniImpl::MiniImpl(const std::filesystem::path& iniFilePath) :
    p{std::make_unique<Impl>(iniFilePath)}
{
}

MiniImpl::~MiniImpl() = default;

void MiniImpl::set(const std::string& section, const std::string& name, const std::string& value)
{
    p->ini[section][name] = value;
}

std::string MiniImpl::get(const std::string& section, const std::string& name) const
{
    return p->ini[section][name];
}

bool MiniImpl::updateIniFile()
{
    return p->iniFile.write(p->ini);
}

}