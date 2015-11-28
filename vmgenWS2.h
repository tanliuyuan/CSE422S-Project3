#pragma once
#include <string>
#include <random>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <vector>
using namespace std;

class vmgenWS
{
public:

	vmgenWS(int size, int lb, int ub, int range, int length, string file) : ws_size(size), LB(lb), UB(ub), seqRange(range), seqLength(length), genFile(file) {}
	int generateFile();

private:


	int ws_size, LB, UB, seqLength, seqRange;
	int referencesCreated, num_gen, ref = 0;
	vector<int> ws;
	bool reroll = false;
	//default_random_engine intGenerate;
	random_device rand1, rand2, rand3;
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
