#ifndef ALU_H
#define ALU_H

#include "table.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>

using namespace std;

int StrtoNum(string SumStr);
string numtoStr(int num);
string AddSum(string sum, int length);
string SubSum(string sum, int length);

#endif