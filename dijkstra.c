/*Algorithms and Data Structures COMP20003
Assignment 2, Semester 2 2014
Author: Lochlan Brick 638126, October 20 2014*/

#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "dijkstra.h"

minpath_t dijkstra(int start, int** graph, int num_vertices) {

	int i;
	heap_t* queue;
	item_t* current_item;
	int* distance = malloc(sizeof(int)*num_vertices);
	int* pred;
	minpath_t shortest_paths;
	
	if((queue = malloc(sizeof(heap_t))) == NULL ||
	((distance = malloc((num_vertices+1)*sizeof(int))) == NULL) ||
	((pred = malloc((num_vertices+1)*sizeof(int))) == NULL)) {
	
		printf("Memory allocation error.\n");
		exit(MALLOCERROR);
	}
	
	/*Initialise queue and arrays*/
	for(i=1; i<=num_vertices; i++) {
		distance[i] = INT_MAX;
		pred[i] = -1;
	}
	distance[start] = 0;
	*queue = make_heap(INIT_HEAP_SIZE);
	
	//Insert all items into the array
	for(i=1; i<=num_vertices; i++) {
		insert(i, distance[i], queue);
	}
	
	/*continue deleting the root from the queue and adjusting the distance 
	array until all items have been dealt with*/
	while(!is_empty(queue)) {
		current_item = delete_min(queue);
		
		//go through each vertex and adjust the distance array
		for(i=1; i<=num_vertices; i++) {
			if(distance[current_item->label] + 
			graph[current_item->label][i] >= 0 
			&& distance[current_item->label] + 
			graph[current_item->label][i] < distance[i]) {
				/*new shortest path found to node 'i', adjust queue and 
				all arrays accordingly*/
				distance[i] = distance[current_item->label] + 
					graph[current_item->label][i];
				decrease_key(queue, i, distance[i]);
				pred[i] = current_item->label;
			}
		}
	}
	shortest_paths.distance = distance;
	shortest_paths.pred = pred;
	return shortest_paths;
}
