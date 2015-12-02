#pragma once
#include <string>
#include <random>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <time.h>
using namespace std;

class vmgenU
{
public:

	vmgenU(int Range, int Length, string File) : genRange(Range), genLength(Length), genFile(File) {} //construct
	int generateFile(); //file generator

private:


	int genRange, genLength, generated; //command line input range & length

	string genFile;
	ofstream outFile;
};


inline bool isInt(const std::string & s)
{
	if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

	char * p;
	strtol(s.c_str(), &p, 10);
    // if strtol returns value of zero to p, no non-numerical values were found. return true
	return (*p == 0);
}
