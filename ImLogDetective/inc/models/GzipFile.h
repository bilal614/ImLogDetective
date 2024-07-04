
#ifndef IMLOGDETECTIVE_MODELS_GZIPFILE_H
#define IMLOGDETECTIVE_MODELS_GZIPFILE_H

#include <filesystem>
#include <sstream>

namespace ImLogDetective
{

class GzipFile
{
public:
    virtual ~GzipFile() = default;
    virtual std::stringstream decompress(const std::filesystem::path& filePath) = 0;
    virtual bool isGzipFormat(const std::filesystem::path& filePath) = 0;
};

}

#endif