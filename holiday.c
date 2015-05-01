/*Algorithms and Data Structures COMP20003
Assignment 2, Semester 2 2014
Author: Lochlan Brick 638126, October 20 2014*/

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>
#include"holiday.h"

//Expect a dense graph, therefore store edges in an array instead.

int main(int argc, char** argv) {
	
	place_t** places;
	minpath_t shortest_paths;
	int num_places;
	int** graph;
	int origin;
	
	places = read_places(argv[1], &num_places);
	graph = read_graph(argv[2], num_places);
		
	origin = get_origin(places, num_places);

	shortest_paths = dijkstra(origin, graph, num_places);
	
	get_destination(places, num_places, shortest_paths.distance, 
		shortest_paths.pred, origin);
		
	return 0;
}


/*Find the cheapest destination that fits the user's holiday criteria, and print
out the places to stop at on the way there.*/
void get_destination(place_t** places, int num_places, int* distance, int* pred, 
	int origin) {
	int i, dest = -1;
	int min = INT_MAX;
	char* continent;
	char cultural, outdoors;
	
	continent = get_continent();
	cultural = get_cultural();
	outdoors = get_outdoors();
	
	for(i=1; i<=num_places; i++) {
		
		/*ignore locations which don't fit criteria*/
		if(cultural == 'Y' && places[i]->cultural != 'y' 
		&& places[i]->cultural != 'Y')
			continue;
		if(outdoors == 'Y' && places[i]->outdoors != 'y' 
		&& places[i]->outdoors != 'Y')
			continue;
		if(strcasecmp(continent, "any") != 0 
		&& strcasecmp(continent, places[i]->continent) != 0)
			continue;
		if(i == origin)
			continue;
		
		/*find lowest cost for places that do fit criteria*/
		if(distance[i] < min) {
			dest = i;
			min = distance[i];
		}
	}

	if (dest == -1) {
		printf("Error: No destinations matched your criteria.\n");
		exit(NORESULT);
	} else {
		printf("%s  $%d\n", places[dest]->name, min);
		get_pred(places, pred, dest);
		printf("\n");
	}
}


/*Print out the places stopped at to get to a given place.*/
void get_pred(place_t** places, int* pred, int placeID) {
	/*recursively check the predecessors along the shortest path, printing 
	them in chronological order.*/
	if(pred[placeID] != -1) 
		get_pred(places, pred, pred[placeID]);	
	printf("%s ", places[placeID]->name);
}


/*Repeatedly prompts user for a starting point for their holiday until a valid
input is given.*/
int get_origin(place_t** places, int num_places) {
	char buffer[MAXCHARS];
	char* origin;
	int length, i;
	
	printf("Enter your starting point:\n");
	if(scanf("%s", buffer) != 1) {
		printf("Error: input can have only one argument.\n");
		exit(INPUTERROR);
	}
	
	//skip new line character
	getchar();
	length = strlen(buffer);
	
	if((origin = malloc((length+1)*sizeof(char))) == NULL) {
		printf("Memory allocation error.\n");
		exit(MALLOCERROR);
	}
	
	strncpy(origin, buffer, length+1);
	
	for(i=1; i<=num_places; i++) {
		if(strcasecmp(origin, places[i]->name) == 0)
			return i;
	}
	
	printf("Error: input did not match any known places. Try again.\n");
	return get_origin(places, num_places);
}


/*Repeatedly prompts user for their preferred continent until a valid input 
is given.*/
char* get_continent() {

	char buffer[MAXCHARS];
	char* continent;
	int length;
	int i, valid=0;
	char continents[7][15] = {"Australia", "Asia", "NorthAmerica", 
		"SouthAmerica", "Europe", "Africa", "Antarctica"};
	
	while(!valid) {
	
		printf("Enter the continent you prefer: [%s,%s,%s,%s,%s,%s,%s]\n",
			continents[0], continents[1], continents[2], continents[3],
			continents[4], continents[5], continents[6]);
		
		//if input is empty, assume any continent is acceptable
		fgets(buffer, MAXCHARS, stdin);
		if(strcmp(buffer, "\n") == 0) 
			return "any";
		
		//input is non-empty, remove '\n' character at the end of the string
		buffer[strlen(buffer)-1]=0;
		
		length = strlen(buffer);
		
		for(i=0; i<NUMCONTINENTS; i++) {
			if(strcasecmp(buffer, continents[i]) == 0)
				break;
		}
		
		//check whether input was a valid continent
		if(i<7)
			valid = 1;
		else
			printf("Invalid continent. Try again.\n");
	}
	
	if((continent = malloc((length+1)*sizeof(char))) == NULL) {
		printf("Memory allocation error.\n");
		exit(MALLOCERROR);
	}
	
	strncpy(continent, continents[i], length+1);
	return continent;
}


/*Repeatedly prompts user for whether they require cultural interest until a 
valid input is given.*/
char get_cultural() {
	
	int valid=0;
	char cultural;
	
	while(!valid) {
	
		printf("Cultural interest required? [Y/N]\n");
		
		cultural = getchar();
		
		if(cultural == 'y' || cultural == 'Y') {
			cultural = 'Y';
			valid = 1;
			//skip new line character
			getchar();
		} else if(cultural == 'n' || cultural == 'N') {
			cultural = 'N';
			valid = 1;
			//skip new line character
			getchar();
		} else if (cultural == '\n') {
			cultural = 'N';
			valid = 1;
		} else {
			//skip new line character
			getchar();
			printf("Invalid input. Try again.\n");
		}
	}
	
	return cultural;
}
	

/*Repeatedly prompts user for whether they require outdoors activities until a 
valid input is given.*/
char get_outdoors() {

	int valid=0;
	char outdoors;
	
	while(!valid) {
	
		printf("Outdoors activities required? [Y/N]\n");
		outdoors = getchar();
		
		if(outdoors == 'y' || outdoors == 'Y') {
			outdoors = 'Y';
			valid = 1;
			//skip new line character
			getchar();
		} else if(outdoors == 'n' || outdoors == 'N') {
			outdoors = 'N';
			valid = 1;
			//skip new line character
			getchar();
		} else if(outdoors == '\n') {
			outdoors = 'N';
			valid = 1;
		} else {
			//skip new line character
			getchar();
			printf("Invalid input. Try again.\n");
		}
	}
	return outdoors;
}
	
	
	
	
	



	





