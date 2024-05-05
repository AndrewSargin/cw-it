#pragma once

#ifndef TECHNICAL_H
#define TECHNICAL_H

#include <vector>
#include <iostream>
#include <map>
#include "entry.h"

using std::vector;
using std::string;


///Разбить строку по разделителям
vector<string> SplitLine(string line, string delimiter);

///Конвертирует полученные для графика данные в то, с чем можно работать
vector<vector<float>> ConvertChartData(std::map<int, Entry>);

#endif // TECHNICAL_H
