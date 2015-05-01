/*Algorithms and Data Structures COMP20003
Assignment 2, Semester 2 2014
Author: Lochlan Brick 638126, October 20 2014*/

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>
#include "readdata.h"


place_t** read_places(char* places_file, int* num_places) {
	FILE* fp;	
	char line[MAXLINELEN];
	place_t** places;
	int count=0;
	int n;
	char arg1[MAXFIELDLEN], arg2[MAXFIELDLEN], arg3[MAXFIELDLEN];
	char arg4[MAXFIELDLEN], arg5[MAXFIELDLEN];	
	int ID;
	
	if ((fp = (FILE*)fopen(places_file, "r")) == NULL) {
		printf("Error: File named '%s' not found or missing.\n", 
			places_file);
		exit(FILEERROR);
	}
		
	if(fgets(line, sizeof(line), fp) == NULL) {
		printf("Error: file seems to be empty.\n");
		exit(FILEERROR);
	}
	
	*num_places = atoi(line);
	
	if((places = malloc((*num_places + 1)*sizeof(place_t*))) == NULL) {
		printf("Memory allocation error.\n");
		exit(MALLOCERROR);
	}
	
	//keep reading place data until the end of the file is reached
	while(fgets(line, sizeof(line), fp) != NULL) {
	
		if(sscanf(line, "%s %s %s %s %s", arg1, arg2, arg3, arg4, arg5) 
		!= 5) {
			printf("Record number %d is formatted incorrectly\n.", 
				++count);
			exit(INPUTERROR);
		}
		
		if(DEBUG)
			printf("%s %s %s %s %s\n\n", arg1, arg2, arg3, arg4, arg5);
			
		if((ID = atoi(arg1)) > *num_places) {
			printf("Error: invalid place ID.\n");
			exit(INPUTERROR);
		}
		
		/*check and copy each field one by one*/
		if((places[ID] = malloc(sizeof(place_t))) == NULL) {
			printf("Memory allocation error.\n");
			exit(MALLOCERROR);
		}
		
		places[ID]->ID = atoi(arg1);
		
		if((places[ID]->name = malloc((n = 
		(strlen(arg2) + 1))*sizeof(char))) == NULL) {
		
			printf("Memory allocation error.\n");
			exit(MALLOCERROR);
		}
		strncpy(places[ID]->name, arg2, n);
		
		if((places[ID]->continent = malloc((n = 
		(strlen(arg3) + 1))*sizeof(char))) == NULL) {
		
			printf("Memory allocation error.\n");
			exit(MALLOCERROR);
		}
		strncpy(places[ID]->continent, arg3, n);
		
		if(*arg4 != 'Y' && *arg4 != 'y' && *arg4 != 'N' && *arg4 != 'n') {
			printf("Error in input data.\n");
			exit(INPUTERROR);
		}
		places[ID]-> cultural = *arg4;
		
		if(*arg5 != 'Y' && *arg5 != 'y' && *arg5 != 'N' && *arg5 != 'n') {
			printf("Error in input data.\n");
			exit(INPUTERROR);
		}
		places[ID]-> outdoors = *arg5;
		count++;
	}
	
	if(count!=*num_places) {
		printf("Error: wrong number of places in input.\n");
		exit(INPUTERROR);
	}
	
	return places;
}


int** read_graph(char* graph_file, int num_places) {

	FILE* fp;
	int** graph;
	char line[MAXLINELEN];
	int from_ID, to_ID, cost, i, j;
	char arg1[MAXFIELDLEN], arg2[MAXFIELDLEN], arg3[MAXFIELDLEN];
	int count=0;

	if ((fp = (FILE*)fopen(graph_file, "r")) == NULL) {
		printf("Error: file named '%s' not found or missing.\n", graph_file);
		exit(FILEERROR);
	}
	
	if((graph = malloc((num_places + 1)*sizeof(int*))) == NULL) {
		printf("Memory allocation error.\n");
		exit(MALLOCERROR);
	}
	
	for(i=1; i<=num_places; i++) {
		if((graph[i] = malloc(num_places*sizeof(int))) == NULL) {
			printf("Memory allocation error.\n");
			exit(MALLOCERROR);
		}
		for(j=1; j<=num_places; j++) {
			if(i==j)
				graph[i][j] = 0;
			else
				graph[i][j] = INT_MAX;
		}	
	}
	//keep reading edge data until the end of the file is reached
	while(fgets(line, sizeof(line), fp) != NULL) {
	
		if(sscanf(line, "%s %s %s", arg1, arg2, arg3) != 3) {
			printf("Error: record number %d formatted incorrectly.\n", 
				++count);
			exit(INPUTERROR);
		}
		
		from_ID = atoi(arg1);
		to_ID = atoi(arg2);
		cost = atoi(arg3);
		
		if(DEBUG)
			printf("from: %d, to: %d, cost: %d\n", from_ID, to_ID, cost);
	
		graph[from_ID][to_ID] = cost;
		count++;	
	}
	
	if(count==0) {
		printf("Error: no data read from file '%s'.\n", graph_file);
		exit(FILEERROR);
	}
	
	return graph;
	
}

void print_places(place_t** places, int num_places)
{
	int i;
	
	for(i=0; i<num_places; i++)
	{
		printf("%d %s %s %c %c\n", 
			places[i]->ID, 
			places[i]->name,
			places[i]->continent,
			places[i]->cultural,
			places[i]->outdoors);
	}
}


void print_graph(int** graph, int dimension)
{
	int i, j, dist;
	for(i=1; i<=dimension; i++) {
		for(j=1; j<=dimension; j++) {
		
			if(graph[i][j] == INT_MAX)
				dist=-1;
			else dist = graph[i][j];
			printf("%5d ", dist);
		}
		printf("\n");
	}
}
	
		
		
		
		
		
		
		
		
