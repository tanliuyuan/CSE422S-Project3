#pragma once
#include <string>
#include <random>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
using namespace std;

class vmgenU
{
public:

	vmgenU(int Range, int Length, string File) : genRange(Range), genLength(Length), genFile(File) {}
	int generateFile();

private:


	int genRange, genLength, generated;
	//default_random_engine intGenerate;
	random_device rand;
	string genFile;
	ofstream outFile;
};


inline bool isInt(const std::string & s)
{
	if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

	char * p;
	strtol(s.c_str(), &p, 10);

	return (*p == 0);
}
