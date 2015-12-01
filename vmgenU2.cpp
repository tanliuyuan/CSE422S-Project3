//-----------------vmgenU----------------------
//David Latulipe
//CSE 422 Project 3
//Due December 1st 
//-----------------vmgenU---------------------
#include "vmgenU.h"
using namespace std;

// arg1 = range of page references. arg2= number of page references.  arg3= filename.
int main(int argc, char *argv[])
{
	int arg1,arg2;
	string arg3;
	if (argc == 4)
	{
		if (isInt(argv[1])) arg1 = atoi(argv[1]);
		else cout << "vmgenU requires 3 arguments: int range, int number, and filename\n";
		if (isInt(argv[2])) arg2 = atoi(argv[2]);
		else cout << "vmgenU requires 3 arguments: int range, int number, and filename\n";
		arg3 = argv[3];
		vmgenU vmgen(arg1, arg2, arg3); //initialize vmgenU with command line data
		vmgen.generateFile(); // run the generator

	}
	else cout << "vmgenU requires 3 arguments: int range, int number, and int filename\n";
	return 0;
}

int vmgenU::generateFile()
{
	mt19937 generator(time(NULL)); // pseudo random generator, clock as seed
	uniform_int_distribution<int> intDistribute(0, genRange - 1); //uniform generator in our needed range
	outFile.open(genFile);
	for (int i = 0; i < genLength; ++i) //create specified page referenced
	{
		generated = intDistribute(generator); //uniformly generate a number, using mt19937 as its source.
		outFile << generated << ' ';
	}
	outFile.close();
	return 0;
}
