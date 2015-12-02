Programming Assignment 3 – Virtual Memory Page Replacement Policies

This assignment is a program that simulates the virtual memory page replacement algorithms
described in section 8.2 of the text book: Optimal (OPT), Least Recently Used (LRU),
First-In-First-Out (FIFO), and the single use-bit one-handed clock policy (CLOCK). 

This project will require three separate executables: a page replacement simulator vmsim,
and two page reference generators: vmgenU and vmgenWS.

To compile the .cpp source code and produce the executables, run the make file by calling “make” under the source file folder. This call will automatically generate all three executables.

To delete the executables, run “make clean” under the source file folder.

-------------------------------------------------------------------------------------------
vmsim 
-------------------------------------------------------------------------------------------

Example: ./vmsim 3 vmrefs.txt LRU

accepts three command-line arguments in the following order:
 (a) the total number of physical memory frames (maximum 100),
 (b) an input filename where a sequence of page references is stored,
 (c) the chosen algorithm (OPT, LRU, FIFO, or CLOCK).
The four possible values for (c) are the strings “opt” or “OPT”, “lru” or “LRU”, “fifo” or
“FIFO”, and “clock” or “CLOCK”. If vmsim is run with the wrong arguments or no
arguments, it prints out usage instructions and exits. 

vmsim first reads all the memory references from the input file and stores them in a local
array. Then, it plays back these references one by one and prints out for each reference the
current allocation state of physical memory frames in the following format:

34: [51| 7|34| | ]

This line means that after using page 34, frames 0, 1 and 2 are occupied by pages 51, 7 and
34, and frames 3 and 4 are empty. One-digit page numbers have an extra space to the left
so that frame numbers are always 2 characters wide (2 spaces for an empty frame). Each
page fault is be signaled by an F character two spaces to the right of the closed bracket,
for example:

45: [45| 7|34| 0| 8] F


This indicates that a page fault occurred when referencing page 45 and that this page was
loaded into frame 0, replacing whichever page was located there beforehand.
After processing all the memory references, vmsim prints the total number of
page faults and the miss rate (page faults divided by number of references). It starts
counting page faults and page references only after all frames have been initially filled.

-------------------------------------------------------------------------------------------
vmgenU
------------------------------------------------------------------------------------------- 

Example: ./vmgenU 10 200 vmrefs.txt

accepts three command-line arguments in the following order:
 (a) the range of page references (maximum 100)
 (b) the length of the sequence of page references
 (c) the name of the file that will be generated. 
If vmgenU is run with the wrong arguments, it prints out usage instructions and exits.

vmgenU generates a sequence of page references of the desired length containing
random page numbers uniformly drawn between 0 and the range minus one. vmgenU writes
this sequence into the file given as input.

-------------------------------------------------------------------------------------------
vmgenWS
-------------------------------------------------------------------------------------------

Example: ./vmgenWS 5 8 15 25 200 vmrefs.txt

accepts six command-line arguments in the following order:
 (a) ws_size: the size of the working set,
 (b) LB – the lower bound on the number of pages to generate in a given working set, 
 (c) UB – the upper bound on the number of pages to generate in a given working set,
 (d) the range of page references (maximum 100),
 (e) the length of the sequence of page references,
 (f) the name of the file that will be generated. 
If vmgenWS is run with the wrong arguments, it prints out usage instructions and exits.

vmgenWS generates a sequence of page references of the desired length (i.e., 200)
containing random page numbers generated as follows:
1. generate num_gen – randomly generate a number between (LB) and (UB).
2. generate (ws_size) page reference numbers in range 0 to (range)
3. randomly generate num_gen of page references from the set of page
     references found in 2 (i.e., if num_gen is 12, we would generate 12 numbers
     from the set of numbers from step 2).
4. repeat steps 1-3 until (length) page references have been generated.
