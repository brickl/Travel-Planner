/*Algorithms and Data Structures COMP20003
Assignment 2, Semester 2 2014
Author: Lochlan Brick 638126, October 20 2014

Contains the elementary functions required to implement a heap.  These include
heap construction, insertion and deletion, as well as upheap and downheap
capabilities.*/

#define MALLOCERROR -2

typedef struct item_t {
	int key;
	int label;
} item_t;

typedef struct heap_t {
	item_t** root;
	int size;
	int capacity;
	int* index;
} heap_t;

/*Creates a heap with an initial size of max_size.*/
heap_t make_heap(int max_size);

/*Inserts a new item, as specified by the label and key arguments, into the 
heap.*/
heap_t* insert(int label, int key, heap_t* heap);

/*Moves an item up through the heap until it meets the heap's condition.*/
void upheap(heap_t* heap, int n);

/*Uses an index to decrease the key of the item specified by 'label', and then
fixes the heap accordingly.*/
void decrease_key(heap_t* heap, int label, int new_key);

/*Deletes the root item of the minimum heap, fixes the heap and then returns
the deleted item.*/
item_t* delete_min(heap_t* heap);

/*Moves an item down through the heap until it meets the heap's condition.*/
void downheap(heap_t* heap, int n);

/*Returns 0 if the heap is empty, otherwise a 1.*/
int is_empty(heap_t* heap);


