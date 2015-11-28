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
		vmgenU vmgen(arg1, arg2, arg3);
		vmgen.generateFile();

	}
	else cout << "vmgenU requires 3 arguments: int range, int number, and int filename\n";
	return 0;
}

int vmgenU::generateFile()
{
	mt19937 generator(rand());
	uniform_int_distribution<int> intDistribute(0, genRange - 1);
	outFile.open(genFile);
	for (int i = 0; i < genLength; ++i)
	{
		generated = intDistribute(generator);
		outFile << generated << ' ';
	}
	outFile.close();
	return 0;
}
