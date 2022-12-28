#include <filesystem>
#include <cstdint>

class BlockFS{
    public:
        BlockFS(std::string path);
        std::filesystem::path path;
        uint64_t blkFilesNum; //The number of available blocks files
    public:
        bool getNumBlockFiles(std::string relPath);
};
