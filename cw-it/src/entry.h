#ifndef ENTRY_H
#define ENTRY_H

#include <iostream>
#include <vector>
#include <map>

class Entry
{

public:
    Entry(std::string line);
    Entry();
    std::map<std::string, std::string> properties;
};

#endif // ENTRY_H
