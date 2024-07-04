#include "models/GzipFileImpl.h"
#include <memory>
#include <cstring>
#include <fstream>
#include <functional>
#include <sstream>
#include <cstdio>
#include <iostream>
#include <zlib.h>

namespace {

constexpr int GZIP_HEADER_DECLARATION[2] = {0x1f, 0x8b}; 
constexpr int CHUNK = 16384;

}

namespace ImLogDetective
{

struct GzipFileImpl::Impl
{
    struct ScopedFile{
        std::unique_ptr<FILE, std::function<void(FILE*)>> inputFile;

        ScopedFile(const std::filesystem::path& filePath) :
            inputFile{fopen(filePath.string().c_str(), "r"), [&](FILE* f){fclose(f);}}
        {
        }
        ~ScopedFile() = default;

        FILE* operator()() 
        {
            return inputFile.get();
        }
    };

    struct ScopedZStream{
        ScopedZStream()
        {
            strm.zalloc = Z_NULL;
            strm.zfree = Z_NULL;
            strm.opaque = Z_NULL;
            strm.avail_in = 0;
            strm.next_in = Z_NULL;
            auto retval = inflateInit2(&strm, 15+16); //15 when deflateInit2 was not used and 16 for gzip format
            if (retval != Z_OK) 
            {
                throw std::bad_alloc();
            }
        }
        ~ScopedZStream()
        {
            inflateEnd(&strm);
        }
        z_stream strm;
    };

    Impl();
    ~Impl();
    std::stringstream decompress(const std::filesystem::path& filePath);
    size_t getFileSize(const std::filesystem::path& filePath);

    char in[CHUNK];
    char out[CHUNK];
};

GzipFileImpl::Impl::~Impl()
{
}

GzipFileImpl::Impl::Impl() :
    in{'\0'},
    out{'\0'}
{
}

size_t GzipFileImpl::Impl::getFileSize(const std::filesystem::path& filePath)
{
    std::ifstream file{filePath, std::ios::binary | std::ios::ate};
    return file.tellg();
}

bool GzipFileImpl::isGzipFormat(const std::filesystem::path& filePath)
{
    std::ifstream file{filePath, std::ios::binary | std::ios::ate};
    file.seekg(0);
    char gzipHeader[2] = {'\0'};
    file.read(gzipHeader, 2);
    auto result = static_cast<unsigned char>(gzipHeader[0]) == GZIP_HEADER_DECLARATION[0] && static_cast<unsigned char>(gzipHeader[1]) == GZIP_HEADER_DECLARATION[1];
    return result;
}

std::stringstream GzipFileImpl::Impl::decompress(const std::filesystem::path& filePath)
{
    ScopedZStream zStrm;
    int retval = 0;
    std::stringstream result;
    Impl::ScopedFile source{filePath}; 
    do
    {
        zStrm.strm.avail_in = fread(in, 1, CHUNK, source());
        if (ferror(source())) 
        {
            (void)inflateEnd(&zStrm.strm);
            break;
        }
        if (zStrm.strm.avail_in == 0)
        {
            break;
        }
        zStrm.strm.next_in = (Bytef *) in;
        do {
            int have;
            zStrm.strm.avail_out = CHUNK;
            zStrm.strm.next_out = (Bytef *) out;
            retval = inflate(&zStrm.strm, Z_NO_FLUSH);
            if (retval == Z_STREAM_ERROR) {
                throw std::bad_alloc();
            }
            have = CHUNK - zStrm.strm.avail_out;
            result << std::string(out, have);
        } while (zStrm.strm.avail_out == 0);
    } while (retval != Z_STREAM_END);

    return result;
}

GzipFileImpl::GzipFileImpl() :
    p{std::make_unique<Impl>()}
{
}

GzipFileImpl::~GzipFileImpl() = default;

std::stringstream GzipFileImpl::decompress(const std::filesystem::path& filePath)
{
    if(!isGzipFormat(filePath))
    {
        std::cerr << "ERROR: File is not gzip format" << std::endl;
    }
    return p->decompress(filePath);
}

}