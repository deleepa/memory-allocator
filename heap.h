#ifndef HEADER_HEAPS
#define HEADER_HEAPS

#include "program.h"

void heapify(Program *arrayToHeapify, int nodeToStartAt, int sizeOfHeap);
void buildHeap(Program *arrayToBuildHeapFrom, int sizeOfArray);
void heapInsert(Program *heapToInsertValueInto, Program valueToBeInserted, int sizeOfHeap);
Program heapExtractMax(Program *heapToExtractMaxFrom, int sizeOfHeap);
#endif
