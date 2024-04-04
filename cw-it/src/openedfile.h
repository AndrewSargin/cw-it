#ifndef OPENEDFILE_H
#define OPENEDFILE_H

#include <map>
#include <vector>
#include <string>
#include "entry.h"

class OpenedFile
{
public:
    OpenedFile();
    std::string filePath;
    std::string fileName;
    std::map<int, Entry> data;
};

#endif // OPENEDFILE_H
