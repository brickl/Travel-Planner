holiday: readdata.o holiday.o dijkstra.o minheap.o
	gcc -Wall -o holiday readdata.o holiday.o dijkstra.o minheap.o

readdata.o: readdata.c readdata.h
	gcc -Wall -c readdata.c
	
holiday.o: holiday.c holiday.h
	gcc -Wall -c holiday.c
	
dijkstra.o: dijkstra.c dijkstra.h
	gcc -Wall -c dijkstra.c
	
minheap.o: minheap.c minheap.h
	gcc -Wall -c minheap.c


