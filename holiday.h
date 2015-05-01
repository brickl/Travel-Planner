/*Algorithms and Data Structures COMP20003
Assignment 2, Semester 2 2014
Author: Lochlan Brick 638126, October 20 2014

Contains the main program for an application that returns the cheapest 
destination for a holidayer to get to, based on their preferences and a set
of travel costs between places.*/

#define FILEERROR -1
#define MALLOCERROR -2
#define INPUTERROR -3
#define NORESULT -4
#define MAXCHARS 256
#define MAXFIELDLEN 20
#define DEBUG 0

#define NUMCONTINENTS 7

typedef struct place_t
{
	int ID;
	char* name;
	char* continent;
	char cultural;
	char outdoors;
} place_t;

typedef struct minpath_t
{
	int* distance;
	int* pred;
} minpath_t;

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

/*Uses Dijkstra's algorithm to find and return the distances and routes
associated with the shortest path from the node 'start' to every other node
in a graph.*/
minpath_t dijkstra(int start, int** graph, int num_vertices);

/*Prompts the user for the origin of their holiday, and returns the ID of this
place.*/
int get_origin(place_t** places, int num_places);

/*Prompts the user to input whether or not they require cultural interests on
their holiday, and returns a y if they do and an n if they do not.*/
char get_cultural();

/*Prompts the user to input whether or not they require outdoors activities on 
their holiday, and returns a y if they do and an n if they do not.*/
char get_outdoors();

/*Prompts the user to input their preferred continent for a holiday, and returns 
the name of this continent.*/
char* get_continent();

/*Uses the shortest path array 'distance' to produce and print details
of the cheapest route and holiday destinationan that fits the user's 
preferences.*/
void get_destination(place_t** places, int num_places, int* distance, int* pred,
	int origin);

/*Recursively gathers the places visited en route to the place
with placeID equal to 'current', and prints these places out in order.*/
void get_pred(place_t** places, int* pred, int current);

