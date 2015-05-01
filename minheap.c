/*Algorithms and Data Structures COMP20003
Assignment 2, Semester 2 2014
Author: Lochlan Brick 638126, October 20 2014*/

#include <stdlib.h>
#include <stdio.h>
#include "minheap.h"

heap_t make_heap(int max_size) {
	int i;
	heap_t new_heap;
	
	if((new_heap.root = malloc((max_size+1)*sizeof(item_t*))) == NULL) {
		printf("Memory allocation error.\n");
		exit(MALLOCERROR);
	}
	if((new_heap.index = malloc((max_size+1)*sizeof(int))) == NULL) {
		printf("Memory allocation error.\n");
		exit(MALLOCERROR);
	}
	
	new_heap.size = 0;
	new_heap.capacity = max_size;
	
	for(i=0; i<=max_size; i++) {
		new_heap.index[i] = -1;
	}
	
	return new_heap;
}


heap_t* insert(int label, int key, heap_t* heap) {

	item_t* new_item;
	
	if((new_item = malloc(sizeof(item_t))) == NULL) {
		printf("Memory allocation error.\n");
		exit(MALLOCERROR);
	}
	
	new_item->label = label;
	new_item->key = key;
	
	//if heap is full, increase its size
	if(heap->size >= heap->capacity) {
		heap->capacity *= 2;
		if((heap->root = realloc(heap->root, 
			(heap->capacity+1)*sizeof(item_t*))) == NULL) {
			
			printf("Memory allocation error.\n");
			exit(MALLOCERROR);
		}
		if((heap->index = realloc(heap->index, 
			(heap->capacity+1)*sizeof(int))) == NULL) {
			
			printf("Memory allocation error.\n");
			exit(MALLOCERROR);
		}
	}
	//add new item to end of heap array
	heap->root[++(heap->size)] = new_item;
	heap->index[label] = heap->size;
	//fix the heap once this new item has been added
	upheap(heap, heap->size);

	return heap;
}


void upheap(heap_t* heap, int n) {

	item_t* tmp;
	item_t** queue = heap->root;
	
	tmp = queue[n];
	
	while(n>1 && tmp->key < queue[n/2]->key) {
		
		queue[n] = queue[n/2];
		heap->index[queue[n/2]->label] = n;
		n /= 2;
	}
	
	queue[n] = tmp;
	heap->index[tmp->label] = n;
}

void decrease_key(heap_t* heap, int label, int new_key) {
	int n = heap->index[label];
	
	if((heap->root[n])->key < new_key)
		return;
				
	(heap->root[n])->key = new_key;
			
	upheap(heap, n);
}

item_t* delete_min(heap_t* heap)
{
	item_t* tmp;
	item_t** queue = heap->root;
	
	//swap root with last element in array, updating index along the way
	tmp = queue[1];
	queue[1] = queue[heap->size];
	heap->index[queue[heap->size]->label] = 1;
	
	queue[heap->size] = tmp;
	heap->index[tmp->label] = heap->size--;
	
	downheap(heap, 1);
	
	return tmp;
}

void downheap(heap_t* heap, int n)
{
	int m;
	item_t* tmp;
	item_t** queue = heap->root;
	
	tmp = queue[n];
	
	while(n <= heap->size/2) {
		m=2*n;
		
		//pick the smallest child
		if(m < heap->size && queue[m]->key > queue[m+1]->key) {
			m++;
		}
		
		if(tmp->key <= queue[m]->key)
			break;
		
		queue[n] = queue[m];
		heap->index[queue[m]->label] = n;
		n = m;
	}
	queue[n] = tmp;
	heap->index[tmp->label] = n;
}


int is_empty(heap_t* heap) {
	return !(heap->size);
}

	
	





