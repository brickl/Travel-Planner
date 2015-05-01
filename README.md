# Travel-Planner
A program to find the cheapest holiday destination to travel to based on some basic criteria, written in C.  Written for the University of Melbourne Subject COMP20003 Algorithms & Data Structures.

Run via the command "make holiday"

This program takes two input files as command line arguments:

The first file is a list of locations, each of which is accompanied by data about whether each places has cultural and or outdoor activities.
This is in the form (placeID placename continent culturalactivities? outdooractivities?)
i.e. "2, Melbourne, Australia, Y, N" means that Melbourne is a place in Australia that has cultural activities available, but no outdoor activities.

The second file contains data about the costs of travelling between different locations.
This is in the form (originID, destinationID, cost)
i.e. "Melbourne Sydeny 150" means that there is a flight available from Melbourne to Sydney for a price of $150

When the program is run, the user is prompted to enter their current destination, their preferred continent to travel to, and whether or not they require/want cultural or outdoor activities.
The program then returns the cheapest destination that satisfies these criteria, the price of travelling to this destination and the cheapest route to take (i.e. via multiple stopovers)

The program implements Dijkstra's algorithm for finding the shortest path in a graph.  
Example input files are included.  These are named "places" and "costs" respectively.

