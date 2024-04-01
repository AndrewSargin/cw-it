#ifndef FILESTRUCTURE_H
#define FILESTRUCTURE_H

#include <vector>
#include <string>

struct openedFile
{
    std::string filePath;
    std::string fileName;
    std::vector<std::vector<std::string>> data;
    std::vector<std::string> id;
    std::vector<std::string> type;
    std::vector<std::string> cpu;
    std::vector<std::string> gpu;
    std::vector<std::string> ram;
    std::vector<std::string> memory;
    std::vector<std::string> date;
    std::vector<std::string> price;
}  ;

#endif // FILESTRUCTURE_H
