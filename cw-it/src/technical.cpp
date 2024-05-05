#include "technical.h"
#include <map>
#include <entry.h>
#include <constants.h>

///Разбиение строки по разделителям
vector<string> SplitLine (string line, string delimiter)
{
    vector<string> vector;
    string token = "";
       for (int i = 0; i < (int) line.size(); i++) {
           bool flag = true;
           for (int j = 0; j < (int) delimiter.size(); j++) {
               if (line[i + j] != delimiter[j]) flag = false;
           }
           if (flag) {
               vector.push_back(token);

               if (token.size() > 0) {
                   token = "";
                   i += delimiter.size() - 1;
               }
           } else {
               token += line[i];
           }
       }
       vector.push_back(token);

    return vector;
}

///Конвертирует полученные для графика данные в то, с чем можно работать
vector<vector<float>> ConvertChartData(std::map<int, Entry> table)
{
    vector<vector<float>> data;

    for (auto i = table.begin(); i != table.end(); i++)
    {
        float ramFloat = 0;
        float memoryFloat = 0;
        float costFloat = 0;
        string ramStr = i->second.properties.at(entryProps[4]);
        if (ramStr != "")
            ramFloat = std::stof(SplitLine(ramStr, " ")[0]);
        else continue;

        string memoryStr = i->second.properties.at(entryProps[5]);
        if (memoryStr != "")
        {
            vector<string> memoryStrVector = SplitLine(memoryStr, "+");
            for (int j = 0; j < (int) memoryStrVector.size(); j++)
            {
                vector<string> memoryStrSubVector = SplitLine(memoryStrVector[j], " ");

                if (memoryStrSubVector[1] == "Гб")
                    memoryFloat += std::stof(memoryStrSubVector[0]);
                else memoryFloat += std::stof(memoryStrSubVector[0]) * 1024;

            }

        }
        else continue;

        costFloat = std::stof(i->second.properties.at(entryProps[9]));
        vector<float> vector;
        vector.push_back(ramFloat);
        vector.push_back(memoryFloat);
        vector.push_back(costFloat);

        data.push_back(vector);
    }

    return data;
}
