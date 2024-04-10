#include "entry.h"
#include "technical.h"
#include "constants.h"
#include <iostream>
#include <vector>

Entry::Entry(std::string line)
{
    std::string delimiter = ";";
    std::vector<std::string> columnEtries = SplitLine(line, delimiter);

    for(int i = 0; i < (int) columnEtries.size() - 1; i++)
    {
        properties.insert({entryProps[i], columnEtries[i]});
    }
}

Entry::Entry()
{
    for(int i = 0; i < 11; i++)
    {
        properties.insert({entryProps[i], ""});
    }
}

