//David Latulipe
//CSE 422 Project 3
//Due December 1st 

#include "vmgenWS.h"
using namespace std;

// arg1 = range of page references. arg2= number of page references.  arg3= filename.
int main(int argc, char *argv[])
{
	int arg1, arg2, arg3, arg4, arg5, inError = 0;
	string arg6;
	if (argc == 7)
	{
		if (isInt(argv[1])) arg1 = atoi(argv[1]);
		else inError++;
		if (isInt(argv[2])) arg2 = atoi(argv[2]);
		else inError++;
		if (isInt(argv[3])) arg3 = atoi(argv[3]);
		else inError++;
		if (isInt(argv[4])) arg4 = atoi(argv[4]);
		else inError++;
		if (isInt(argv[5])) arg5 = atoi(argv[5]);
		else inError++;
		arg6 = argv[6];
		if (inError) cout << "vmgenWS requires 5 arguments: int ws_size, int LB, in UB, int range, and filename\n";
		else
		{
			vmgenWS vmgen(arg1, arg2, arg3, arg4, arg5, arg6);
			vmgen.generateFile();
		}

	}
	else inError++;
	return 0;
}

int vmgenWS::generateFile()
{
	mt19937 generator1(rand1());
	mt19937 generator2(rand2());
	mt19937 generator3(rand3());
	uniform_int_distribution<int> numDistribute(LB, UB - 1);
	uniform_int_distribution<int> rangeDistribute(0, seqRange - 1);
	uniform_int_distribution<int> finalDistribute(0, ws_size - 1);
	outFile.open(genFile);
	while (referencesCreated < seqLength)
	{
		ws.clear();
		num_gen = numDistribute(generator1);
		for (int i = 0; i < ws_size; ++i)
		{
			reroll = false;
			ref = rangeDistribute(generator2);
			for (int k = 0; k < i; ++k)
			{
				if (ref == ws[k]) reroll = true;

			}
			if (!reroll) ws.push_back(ref);
			else --i;
		}
		for (int i = 0; i < num_gen; ++i)
		{
			if (referencesCreated < seqLength)
			{
				ref = finalDistribute(generator3);
				outFile << ws[ref] << ' ';
				referencesCreated++;
			}
		}
	}
	outFile.close();

	return 0;
}
