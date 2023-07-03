#include "models/GzipFile.h"
#include <memory>
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

namespace LogAnalyzerTool
{

struct GzipFile::Impl
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

    Impl();
    ~Impl();
    std::stringstream decompress(const std::filesystem::path& filePath);
    size_t getFileSize(const std::filesystem::path& filePath);

    int retval;
    unsigned int have;
    z_stream strm;
    char in[CHUNK];
    char out[CHUNK];

};

GzipFile::Impl::~Impl()
{
    inflateEnd(&strm);
}

GzipFile::Impl::Impl() : 
    retval{0},
    in{'\0'},
    out{'\0'}
{
    strm.zalloc = Z_NULL;
    strm.zfree = Z_NULL;
    strm.opaque = Z_NULL;
    strm.avail_in = 0;
    strm.next_in = Z_NULL;
    retval = inflateInit2(&strm, 15+16); //15 when deflateInit2 was not used and 16 for gzip format
    if (retval != Z_OK) {
        throw std::bad_alloc();
    }
}

size_t GzipFile::Impl::getFileSize(const std::filesystem::path& filePath)
{
    std::ifstream file{filePath, std::ios::binary | std::ios::ate};
    return file.tellg();
}

bool GzipFile::isGzipFormat(const std::filesystem::path& filePath)
{
    std::ifstream file{filePath, std::ios::binary | std::ios::ate};
    file.seekg(0);
    char gzipHeader[2] = {'\0'};
    file.read(gzipHeader, 2);
    auto result = static_cast<unsigned char>(gzipHeader[0]) == GZIP_HEADER_DECLARATION[0] && static_cast<unsigned char>(gzipHeader[1]) == GZIP_HEADER_DECLARATION[1];
    return result;
}

std::stringstream GzipFile::Impl::decompress(const std::filesystem::path& filePath)
{
    std::stringstream result;
    Impl::ScopedFile source{filePath}; 
    do
    {
        strm.avail_in = fread(in, 1, CHUNK, source());
        if (ferror(source())) {
            (void)inflateEnd(&strm);
            break;
        }
        if (strm.avail_in == 0)
        {
            break;
        }
        strm.next_in = (Bytef *) in;
        do {
            int have;
            strm.avail_out = CHUNK;
            strm.next_out = (Bytef *) out;
            retval = inflate(&strm, Z_NO_FLUSH);
            if (retval == Z_STREAM_ERROR) {
                throw std::bad_alloc();
            }
            have = CHUNK - strm.avail_out;
            result << std::string(out, have);
        } while (strm.avail_out == 0);
    } while (retval != Z_STREAM_END);
    return result;
}

GzipFile::GzipFile() :
    p{std::make_unique<Impl>()}
{
}

GzipFile::~GzipFile() = default;

std::stringstream GzipFile::decompress(const std::filesystem::path& filePath)
{
    if(!isGzipFormat(filePath))
    {
        std::cout << "ERROR: File is not gzip format" << std::endl;
    }
    return p->decompress(filePath);
}

}