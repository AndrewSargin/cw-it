#ifndef FILESTRUCTURE_H
#define FILESTRUCTURE_H

#include <vector>
#include <string>
#include <entity.h>

struct openedFile
{
    std::string filePath;
    std::string fileName;
    std::vector<entity> data;
};

#endif // FILESTRUCTURE_H
