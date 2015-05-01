/*Algorithms and Data Structures COMP20003
Assignment 2, Semester 2 2014
Author: Lochlan Brick 638126, October 20 2014

Contains a function capable of implementing Dijkstra's algorithm using a 
priority queue, and returning both the shortest distance to any other node in a 
graph given a node to start at, as well as the path that gives this shortest
distance.*/

#define MAXVERTICES 100
#define MALLOCERROR -2
#define INIT_HEAP_SIZE 4

typedef struct place_t
{
	int ID;
	char* name;
	char* continent;
	char cultural;
	char outdoors;
} place_t;

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


typedef struct minpath_t
{
	int* distance;
	int* pred;
} minpath_t;

/*Uses Dijkstra's algorithm to find and return the distances and routes
associated with the shortest path from the node 'start' to every other node
in a graph.*/
minpath_t dijkstra(int start, int** graph, int num_vertices);

/*Returns 0 if the heap is empty, otherwise a 1.*/
int is_empty(heap_t* heap);

/*Deletes the root item of the minimum heap, fixes the heap and then returns
the deleted item.*/
item_t* delete_min(heap_t* heap);

/*Creates a heap with an initial size of max_size.*/
heap_t make_heap(int max_size);

/*Inserts a new item, as specified by the label and key arguments, into the 
heap.*/
heap_t* insert(int label, int key, heap_t* heap);

/*Uses an index to decrease the key of the item specified by 'label', and then
fixes the heap accordingly.*/
void decrease_key(heap_t* heap, int label, int new_key);

/*Prints the items in the queue, in order.*/
void print_queue(heap_t* heap);


