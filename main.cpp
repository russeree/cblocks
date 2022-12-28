#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>

// for mmap:
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
//CBlocks Custom
#include <blockfs.hpp>

const char* map_file(const char* fname, size_t& length);

int main()
{
    BlockFS* blockFs = new BlockFS("/home/qrsnap");
    size_t length;
    auto f = map_file("/home/qrsnap/.bitcoin/blocks/blk00001.dat", length);
    auto l = f + length;
    char *file;
    file = (char *)calloc(length, sizeof(char));
    for(int i = 0; i < length; i++){
        file[i] = char(f[i]);
    }
    for (size_t i = 0; i < 100; i++){
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int) static_cast <unsigned char>(file[i]) << ' ';
    }
}

void handle_error(const char* msg) {
    perror(msg);
    exit(255);
}

const char* map_file(const char* fname, size_t& length)
{
    int fd = open(fname, O_RDONLY);
    if (fd == -1)
        handle_error("open");

    // obtain file size
    struct stat sb;
    if (fstat(fd, &sb) == -1)
        handle_error("fstat");

    length = sb.st_size;

    const char* addr = static_cast<const char*>(mmap(NULL, length, PROT_READ, MAP_PRIVATE, fd, 0u));
    if (addr == MAP_FAILED)
        handle_error("mmap");

    // TODO close fd at some point in time, call munmap(...)
    return addr;
}
