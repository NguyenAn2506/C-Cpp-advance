#ifndef __RECORD_HPP
#define __RECORD_HPP

#include <iostream>
#include <string>
#include <ctime>
#include <vector>
#include <cstdio>
#include <cstring>
using namespace std;

bool dataRecord (const char*, vector<int>&, vector<float>&);
bool dataRead(const char*);
void emptyFile(const char*);

#define FAIL 0
#define SUCCCESS 1

#endif // __RECORD_HPP