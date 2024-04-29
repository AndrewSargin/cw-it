#include "technical.h"


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
