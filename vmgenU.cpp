//
//  vmgenU.cpp
//  project3
//
//  Created by Liuyuan Tan on 11/26/15.
//  Copyright © 2015 Liuyuan Tan. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

int main(const int argc, const char* argv[]) {
    if (argc != 4) {
        cout << "Usage: vmgenU [range of page references (maximum 100)] [length of the sequence of page references] [name of file that will be generated]";
        exit(-1);
    }
    else {
        
        // convert argv[1] and argv[2] to intergers
        long rangeOfPageReferences = strtol(argv[1], NULL, 10);
        long lengthOfSequence = strtol(argv[2], NULL, 10);
        
        if (rangeOfPageReferences > 100) {
            cout << "Maximum page reference range: 100";
            exit(-1);
        }
        else {
            
            // open file for output
            ofstream w;
            w.open(argv[3]);
            
            for (int i = 0; i < lengthOfSequence; i++) {
                w << rand() % rangeOfPageReferences << " ";
            }
            w.close();
        }
    }
    return 0;
}