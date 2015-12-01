//
//  vmsim.cpp
//  project3
//
//  Created by Liuyuan Tan, David Latulipe and Corey Glaser on 11/26/15.
//  Copyright © 2015 Liuyuan Tan, David Latulipe and Corey Glaser. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

#define MAXNUMPAGES 1000
#define MAXNUMFRAMES 100

enum ReplacementAlgorithm {
    OPT,
    LRU,
    FIFO,
    CLOCK
};

int LoadInputData(const char* inputFile, long* pageSequence)
{
    ifstream input(inputFile);
    string word;

    int index = 0;
    while (input >> word) {
        pageSequence[index] = strtol(word.c_str(), NULL, 10);
        index++;
    }
    return index;
}

// This function loads an array, which keeps track of the time since the last reference for each page in memory,
// a referencedIndex, which represents the memory frame index of the last referenced page,
// and the index of the largest number in the array (which would represent the page in memory with the longest time since last referenced)
// increments the time since last referenced for all other pages (because they're not referenced),
// and returns the index of the lagest number in LRUTimeSinceLastUsed, which would be the page index to be replaced next in memory
int LRUUpdate(int* timeSinceLastUsed, int numFrames, int referencedIndex, int currentLargestIndex) {
    int largestIndex = currentLargestIndex;
    timeSinceLastUsed[referencedIndex] = -1;
    for (int i = 0; i < numFrames; i++) {
        timeSinceLastUsed[i]++;
        if (timeSinceLastUsed[i] > timeSinceLastUsed[largestIndex]) {
            largestIndex = i;
        }
    }
    return largestIndex;
}

int main(const int argc, const char* argv[])
{
    if (argc != 4) {
        cout << "Usage: vmsim [num frames] [input file] [algorithm]" << endl;
        cout << "Example: vmsim 5 vmrefs.txt LRU" << endl;
        exit(-1);
    }

    const long numFrames = strtol(argv[1], NULL, 10);
    if (numFrames > MAXNUMFRAMES || numFrames <= 0) {
        cout << "Invalid number of frames" << endl;
        exit(-1);
    }

    const char* inputFile = argv[2];

    ReplacementAlgorithm algorithm;
    if (strcmp(argv[3], "OPT") == 0 || strcmp(argv[3], "opt") == 0) algorithm = OPT;
    else if (strcmp(argv[3], "LRU") == 0 || strcmp(argv[3], "lru") == 0) algorithm = LRU;
    else if (strcmp(argv[3], "FIFO") == 0 || strcmp(argv[3], "fifo") == 0) algorithm = FIFO;
    else if (strcmp(argv[3], "CLOCK") == 0 || strcmp(argv[3], "clock") == 0) algorithm = CLOCK;
    else {
        cout << "Invalid replacement algorithm type" << endl;
        exit(-1);
    }

    long pageSequence[MAXNUMPAGES];
    long memoryFrames[MAXNUMFRAMES];
    bool clockUsageBit[MAXNUMFRAMES];//keeps track of each page frames usage bit
    int clockHand = 0;//keeps track of the clock replacement algorithm
    int pageFaultCount = 0;
    int fullPageStartFlag = 0;

    // *** variables for OPT ***
    int OPTCyclesUntilNextRef[MAXNUMFRAMES];
    int OPTIndexOfFurthestRef;

    // *** variables for LRU ***
    // in LRU, keep track of the time since last referenced for each frame
    int LRUTimeSinceLastUsed[MAXNUMFRAMES] = { 0 };
    // the index corresponding to the largest number in LRUTimeSinceLastUsed, which would be the next memory frame index to be replaced
    int LRUCurrentLargestIndex = 0;

    // *** variables for FIFO ***
    // in FIFO, keep track of the next memory frame index to be replaced
    int FIFOReplaceIndex = 0;

    for (int i = 0; i < MAXNUMFRAMES; i++)
    {
        memoryFrames[i] = -1; //initialize entire arrays
        clockUsageBit[i] = false;
    }

    int numPages = LoadInputData(inputFile, pageSequence);

    for (int i = 0; i < numPages; i++) {
        bool pageFault = true;

        // *** Check if page is in memory ***
        for (int j = 0; j < numFrames; j++) {
            // Memory already contains page
            if (memoryFrames[j] == pageSequence[i]) {
                pageFault = false;
                // update the last used array for LRU
                LRUCurrentLargestIndex = LRUUpdate(LRUTimeSinceLastUsed, numFrames, j, LRUCurrentLargestIndex);
                // update clock usage array
                clockUsageBit[j] = true;
            }
        }

        // *** Check if empty frame in memory ***
        if (pageFault)
        {
            for (int j = 0; j < numFrames; j++) {
                // Frame empty, put it there
                if (memoryFrames[j] == -1) {
                    memoryFrames[j] = pageSequence[i];
                    // update the last used array for LRU
                    LRUCurrentLargestIndex = LRUUpdate(LRUTimeSinceLastUsed, numFrames, j, LRUCurrentLargestIndex);
                    clockUsageBit[j] = true;
                    pageFault = false;
                    break;
                }
            }
            if (pageFault && (fullPageStartFlag == 0)) fullPageStartFlag = i;
        }

        // *** Process a page fault ***
        if (pageFault) {
            pageFaultCount++;
            switch (algorithm) {
            case OPT:
                //REPLACEMENT WITH OPT

                // for each page in memory, find when it is next used
                for (int j = 0; j < numFrames; j++) {
                    // loop through rest of sequence to find when used
                    for (int k = i + 1; k < numPages; k++) {
                        // if the page reference is found at this index, remember how far reference is and stop checking
                        if (pageSequence[k] == pageSequence[i]) {
                            OPTCyclesUntilNextRef[j] = k;
                            break;
                        }
                        // if page is not in sequence, set cycle count to high number
                        if (k == numPages - 1) OPTCyclesUntilNextRef[j] = MAXNUMPAGES + 1;
                    }
                }

                // find index of the furthest reference
                OPTIndexOfFurthestRef = 0;
                for (int j = 1; j < numFrames; j++) {
                    if (OPTCyclesUntilNextRef[j] > OPTCyclesUntilNextRef[OPTIndexOfFurthestRef]) OPTIndexOfFurthestRef = j;
                }

                // place page in memory in proper spot
                memoryFrames[OPTIndexOfFurthestRef] = pageSequence[i];
                break;
            case LRU:
                //REPLACEMENT WITH LRU
                memoryFrames[LRUCurrentLargestIndex] = pageSequence[i];
                // update the last used array for LRU
                LRUCurrentLargestIndex = LRUUpdate(LRUTimeSinceLastUsed, numFrames, LRUCurrentLargestIndex, LRUCurrentLargestIndex);
                break;
            case FIFO:
                //REPLACEMENT WITH FIFO
                memoryFrames[FIFOReplaceIndex] = pageSequence[i];
                FIFOReplaceIndex++;
                // if FIFOReplaceIndex reaches the last index in memoryFrames, reset it to 0
                if (FIFOReplaceIndex == numFrames - 1) {
                    FIFOReplaceIndex = 0;
                }
                break;
            case CLOCK:
                //REPLACEMENT WITH CLOCK
                //cycle thru all frames (starting at 0), check the usage bit for that frame
                //if usage bit is not set - replace that page, set its bit, increment clock hand, and exit algorithm
                //if usage is set - set bit to false and continue
                for (int j = 0; j < numFrames + 1; ++j)
                {
                    if (clockUsageBit[clockHand])
                    {
                        clockUsageBit[clockHand] = false;
                        if (++clockHand == numFrames) clockHand = 0; //circular clock
                    }
                    else
                    {
                        memoryFrames[clockHand] = pageSequence[i];
                        if (++clockHand == numFrames) clockHand = 0; //circular clock
                        break;
                    }

                }
                break;
            default:
                cout << "ERROR with replacement algorithm" << endl;
                exit(-1);
            }
        }

        // *** Print memory information ***
        if (pageSequence[i] < 10) cout << ' ';
        cout << pageSequence[i] << ": [";
        for (int j = 0; j < numFrames; j++) {
            if (memoryFrames[j] == -1)                             cout << "  ";
            else if (memoryFrames[j] >= 0 && memoryFrames[j] < 10) cout << " " << memoryFrames[j];
            else if (memoryFrames[j] >= 10)                        cout << memoryFrames[j];
            else {
                cout << "ERROR outputing memory" << endl;
                exit(-1);
            }
            if (j != numFrames - 1) cout << "|";
        }
        cout << "]";
        if (pageFault) cout << " F";
        cout << endl;
    }

    // *** Print miss rate ***
    cout << "Miss rate = " << pageFaultCount << " / " << numPages - fullPageStartFlag << " = " << fixed << setprecision(2) << (double)pageFaultCount / (double)(numPages - fullPageStartFlag) * 100 << "%" << endl;
    return 0;
}
