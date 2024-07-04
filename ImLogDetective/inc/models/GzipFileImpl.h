
#ifndef IMLOGDETECTIVE_MODELS_GZIPFILEIMPL_H
#define IMLOGDETECTIVE_MODELS_GZIPFILEIMPL_H

#include "models/GzipFile.h"
#include <memory>

namespace ImLogDetective
{

class GzipFileImpl : public GzipFile
{
public:
    GzipFileImpl();
    ~GzipFileImpl();
    std::stringstream decompress(const std::filesystem::path& filePath) final;
    bool isGzipFormat(const std::filesystem::path& filePath) final;
private:
    struct Impl;
    std::unique_ptr<Impl> p;
};

}

#endif