#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 3
#  Author: MingWei Dong
#  CruzID: mdong5
#
#  make                     makes FindPath
#  make GraphClient         makes GraphClient
#  make clean               removes binaries
#  make checkFind           tests FindPath for memory leaks on in3
#  make checkClient         tests GraphClient for memory leaks
#------------------------------------------------------------------------------

BASE_SOURCES   = Graph.c List.c
BASE_OBJECTS   = Graph.o List.o
HEADERS        = Graph.h List.h
COMPILE        = gcc -c -std=c11 -Wall -g
LINK           = gcc -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

FindPath : FindPath.o $(BASE_OBJECTS)
	$(LINK) FindPath FindPath.o $(BASE_OBJECTS)

GraphClient : GraphClient.o $(BASE_OBJECTS)
	$(LINK) GraphClient GraphClient.o $(BASE_OBJECTS)

FindPath.o : FindPath.c $(HEADERS)
	$(COMPILE) FindPath.c

GraphClient.o : GraphClient.c $(HEADERS)
	$(COMPILE) GraphClient.c

$(BASE_OBJECTS) : $(BASE_SOURCES) $(HEADERS)
	$(COMPILE) $(BASE_SOURCES)

test : GraphTest.o $(BASE_OBJECTS)
	$(LINK) test GraphTest.o $(BASE_OBJECTS)

GraphTest.o : GraphTest.c $(HEADERS)
	$(COMPILE) GraphTest.c

clean :
	$(REMOVE) FindPath GraphClient FindPath.o GraphClient.o $(BASE_OBJECTS) test GraphTest.o out1 out2 out3 out4 out5
	rm -f *.txt *.sh

checkFind : FindPath
	$(MEMCHECK) FindPath in3 junk3

checkClient : GraphClient
	$(MEMCHECK) 
	
memcheck :
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -v ./FindPath in1 out1

memcheck1 :
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -v ./GraphClient

memcheck2 :
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -v ./test

grade : 
	curl https://raw.githubusercontent.com/houi-lin/cse101-pt.s20/master/pa3/pa3.sh > pa3.sh
	chmod +x pa3.sh
	./pa3.sh