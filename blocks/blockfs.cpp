#include <blockfs.hpp>
#include <iostream>
#include <string>

BlockFS::BlockFS(std::string path){
    this->path = path;
    std::cout << this->path.string();
}

bool BlockFS::getNumBlockFiles(std::string relPath){

}
