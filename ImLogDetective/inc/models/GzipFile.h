#pragma once

#include "models/IGzipFile.h"
#include <memory>

namespace ImLogDetective
{

class GzipFile : public IGzipFile
{
public:
    GzipFile();
    ~GzipFile();
    std::stringstream decompress(const std::filesystem::path& filePath) final;
    bool isGzipFormat(const std::filesystem::path& filePath) final;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}