/*Algorithms and Data Structures COMP20003
Assignment 2, Semester 2 2014
Author: Lochlan Brick 638126, October 20 2014

Contains the functions necessary to read formatted data about a set of places, 
as well as data about the edges of a graph, from a file.  Also contains
functions to print out a list of places and the adjacency matrix of a graph.*/

#define FILEERROR -1
#define MALLOCERROR -2
#define INPUTERROR -3
#define MAXLINELEN 256
#define MAXFIELDLEN 20
#define DEBUG 0

typedef struct place_t
{
	int ID;
	char* name;
	char* continent;
	char cultural;
	char outdoors;
} place_t;

/*Reads in data about places from the file specified by places_file,
and stores the number of places at the address specified by num_places.
Returns a pointer to the list of places.*/
place_t** read_places(char* places_file, int* num_places);

/*Prints out all of the locations in the array 'places'.*/
void print_places(place_t** places, int num_places);

/*Reads the graph data from the file specified by graph_file, and returns a
pointer to this graph.*/
int** read_graph(char* graph_file, int num_places);

/*Prints out the adjacency matrix for the graph at 'graph'.*/
void print_graph(int** graph, int dimension);

