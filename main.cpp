#include <iostream>
#include <cstring>
#include <cstdlib>
#include <execinfo.h>

#include "heap.h"
#include "program.h"
#include "partition.h"
using namespace std;

int main(int argc, char* argv[]) {
	
	//variable declarations
	int lineCounter = 0;
	int noOfPrograms = 0;
	int noOfPartitions = 0;
	Program *programs;
	Partition *partitions;
	int programsArrayCount = 0;
	int programCounter = 0;
	
	FILE *file;

	//check if the program was started properly
	if(argc != 2) {	
		cout << "Missing commandline arguments. Usage: ./main FILENAME" << endl;
		return 0;
	}
	//check if the data file exists
	if(file == NULL) {
		cout << "Error: Missing data.txt file" << endl;
		return 0;
	}
	else {
		string filename = "";
		filename += argv[1];
		file = fopen(filename.c_str(), "r");
		char c;
		string s;
		while(c != EOF) {
			c = getc(file);
			s += c;
			if(c == '\n') {
				lineCounter++;
				if(lineCounter == 1) { 
					// line 1 is here the number of programs and partitions are defined
					size_t index = s.find(' ');
					noOfPartitions = stoi(s.substr(0, index));
					noOfPrograms = stoi(s.substr(index));

					s = ""; //clear the string
				}
				else if(lineCounter == 2) {
					//line 2 is where the partition sizes are defined	
					partitions = new Partition[noOfPartitions];
					programs = new Program[noOfPrograms];
					for(int i = 0; i < noOfPartitions; i++) {
						if(i == (noOfPartitions - 1)) {
							partitions[i].size = stoi(s.substr(0));
						}
						else {
							partitions[i].size = stoi(s.substr(0, s.find(' ')));	
							s.erase(0, s.find(' ') + 1);
						}
						
						partitions[i].id = i + 1;
						partitions[i].runtime = 0;
					}
					s = "";
				}
				else {
					//the program parameters will follow
					//0 0 shows the end of the definitions
					if(s.compare(0, 1, "0") == 0) {
					}
					//process the Program parameters
					else {
						int processCount = atoi(&s.at(0));
						Program temp[processCount];
						
						s.erase(0, 2);
						//for each program, get the number of processes
						for(int i = 0; i < processCount; i++) {	
							//if it is the last process then no spaces exist at the end of the line	
							if(i == (processCount - 1)) {
								
								temp[i].size = stoi(s.substr(0, s.find(' ')));
								s.erase(0, s.find(' ')+1);
								temp[i].time = stoi(s.substr(0));
							}
							else {
								temp[i].size = stoi(s.substr(0, s.find(' ')));
								s.erase(0, s.find(' ')+1);
								temp[i].time = stoi(s.substr(0, s.find(' ')));
								s.erase(0, s.find(' ')+1);
							}
						
						}
						//select the process with the least runtime to add to the main array
						if(processCount > 1) {
							int minRuntime = 0;
							for(int i = 0; i < processCount; i++) {
								if(temp[i].time < temp[minRuntime].time) {
									minRuntime = i;
								}
							}
							temp[minRuntime].id = ++programCounter;
							programs[programsArrayCount++] = temp[minRuntime];
						}
						else {
							temp[0].id = ++programCounter;
							programs[programsArrayCount++] = temp[0];
						}					
					}
					s = "";
				}
			}
		}
		//build a heap from the arrays
		buildHeap(programs, noOfPrograms);		
	}

	int totalTurnaround = 0;
	float turnaroundProgramCount = noOfPrograms;
	do{
		//check the each program against every memory partition
		for(int i = 0; i < noOfPrograms; i++) {
			for(int j = 0; j < noOfPartitions; j++) {
				//when a suitable memory partition is found, add the runtime
				if(programs[i].size <= partitions[j].size) {
					int oldtime = partitions[j].runtime;
					partitions[j].runtime += programs[i].time;
					printf("Program %i runs in region %i from %i to %i \n", programs[i].id, partitions[j].id, oldtime, partitions[j].runtime);
					totalTurnaround += partitions[j].runtime;
					heapExtractMax(programs, noOfPrograms--);
					
					break;
				}
			}
			//use a simple sorting algorithm to sort the programs by runtime - descending
			for(int i = 0; i < noOfPartitions; i++) {
				int j = i;
				while(j > 0 && partitions[j - 1].runtime > partitions[j].runtime) {
					Partition temp = partitions[j];
					partitions[j] = partitions[j - 1];
					partitions[j - 1] = temp;
					j--;
				}	
			}
			break;
		}
	}while(noOfPrograms >= 1); 	

	printf("Average turnaround time is: %.2f \n", (totalTurnaround/turnaroundProgramCount));
	
	return 0;
}
