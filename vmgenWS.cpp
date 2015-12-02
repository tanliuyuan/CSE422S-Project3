//
//  vmgenWS.cpp
//  project3
//
//  Created by Liuyuan Tan on 11/26/15.
//  Copyright © 2015 Liuyuan Tan. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;

int main(const int argc, const char* argv[]) {
    if (argc != 7) {
        cout << "Usage: vmgenWS [size of working set] [lower bound] [upper bound] [range of page references (maximum 100)] [length of the sequence of page references] [name of file that will be generated]";
        exit(-1);
    }
    else {
        
        // convert argv[1], argv[2], argv[3], argv[4], and argv[5] to intergers
        const long wsSize = strtol(argv[1], NULL, 10);
        const long lowerBound = strtol(argv[2], NULL, 10);
        const long upperBound = strtol(argv[3], NULL, 10);
        const long rangeOfPageReferences = strtol(argv[4], NULL, 10);
        const long lengthOfSequence = strtol(argv[5], NULL, 10);
        
        if (rangeOfPageReferences > 100) {
            cout << "Maximum page reference range: 100";
            exit(-1);
        }
        else {
            
            // open file for output
            ofstream w;
            w.open(argv[6]);
            
            // keep track of the total number of page references generated
            int generated = 0;
            
            while (generated < lengthOfSequence) {
                // randomly generate a number between lowerBound and upperBound
                long numGen = (rand() % (upperBound - lowerBound + 1)) + lowerBound;
            
                // generate [wsSize] page reference numbers
                int pageReferenceNums[wsSize];
                for (int i = 0; i < wsSize; i++) {
                    pageReferenceNums[i] = rand() % rangeOfPageReferences;
                }
            
                // randomly generate [numGen] numbers from pageReferenceNums
                for (int i = 0; i < numGen; i++) {
                    if (generated < lengthOfSequence) {
                        w << pageReferenceNums[rand() % wsSize] << " ";
                        generated++;
                    }
                }
            }
            w.close();
        }
    }
    return 0;
}
