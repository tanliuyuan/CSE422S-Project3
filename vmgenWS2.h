#pragma once
#include <string>
#include <random>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
#include <time.h>
using namespace std;

class vmgenWS
{
public:
    //constructor
	vmgenWS(int size, int lb, int ub, int range, int length, string file) : ws_size(size), LB(lb), UB(ub), seqRange(range), seqLength(length), genFile(file) {}
	//file generator
	int generateFile();

private:


	int ws_size, LB, UB, seqLength, seqRange; //command line inputs
	int referencesCreated, num_gen, ref = 0;
	vector<int> ws; //working set array
	bool reroll = false; //used when duplicate values created within set
	//default_random_engine intGenerate;
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
