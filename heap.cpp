#include "heap.h"
#include "program.h"

#include <stdio.h>

int left(int i) {
	return (2 * i) + 1;
}

int right(int i) {
	return (2 * i) + 2;
}

int parent(int i) {
	if(i / 2 == 0) {
		return (i / 2) - 1;
	}
	else {
		return (i / 2);
	}
}

void heapify(Program *a, int i, int heapsize) {

	int l = left(i);
	int r = right(i);
	int minimum;

	if((l < heapsize) && (a[l].time < a[i].time)) {
		minimum = l;
	}
	else {

		minimum = i;
	}

	if((r < heapsize) && (a[r].time < a[minimum].time)) {
		minimum = r;
	}

	if(minimum != i) {
		Program temp = a[minimum];
		a[minimum] = a[i];
		a[i] = temp;

		heapify(a, minimum, heapsize);
	}
}

void buildHeap(Program *a, int size) {
	
	int i; //loop controller
	for(i = ((size - 1) / 2); i >= 0; i--) {
		heapify(a, i, size);
	}

}

void heapInsert(Program *a, Program key, int size) {

	//size++;
	int i = size;

	while((size > 1) && (a[parent(i)].time < key.time)) {
		a[i] = a[parent(i)];
		i = parent(i);
	}
	a[i] = key;
}

Program heapExtractMax(Program *a, int size) {

	if(size >= 1) {
		Program max = a[0];
		
		a[0] = a[size - 1];
		size--;
		heapify(a, 0, size);
		return max;
	}
} 
