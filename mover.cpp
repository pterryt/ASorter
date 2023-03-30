#include "mover.h"
#include <libgen.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <dirent.h>

int moveFiles(std::string& fileName){

    const char* file = fileName.c_str();
    std::cout << file << std::endl;
    if (access(file, F_OK) == -1)
    {
        std::cout << "Stopped move: couldn't open file during move." << std::endl;
        return 0;
    }

    const char* ext = strrchr(file, '.');
    std::cout << ext << std::endl;
    if (!ext)
    {
        std::cout << "Stopped move: file has no extension." << std::endl;
        return 0;
    }

    auto iter = extMList.find(ext);
    if (iter == extMList.end()){
        std::cout << "Stopped move: extension not found on master list." << std::endl;
        return 0;
    }
    else
    {
       const int dest = iter->second;
       const char* destPath = subdirs[dest];
       DIR* dir = opendir(destPath);
       if (!dir)
       {
           std::cout << "Stopped move: couldn't open destination direcotry." << std::endl;
           return 0;
       }
       else
       {
           closedir(dir);
           std::string baseFile(basename(const_cast<char*>(file)));
           std::string dirAsString(destPath);
           if (!rename(file, (dirAsString + baseFile).c_str())){
               std::cout << "Move successful." << std::endl;
               return 1;
           }
           else
           {
               std::cout << "Move failed." << std::endl;
               return 0;
           }
       }
    }
}
