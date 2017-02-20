#include<iostream>
#include<fstream>
#include<map>
#include<algorithm>
#include<vector>
#include "NFA.h"

using namespace std;

#ifndef FILEIO_H
#define FILEIO_H

//Utility functions to load in and write out NFAs and DFAs.
int countChars(string in, char delimeter);
vector<string> splitString(string in, char delimeter);
NFA readFile(char* filename); //Take in a file and return a NFA.



#endif
