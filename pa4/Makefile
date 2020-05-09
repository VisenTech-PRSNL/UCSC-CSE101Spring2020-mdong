#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 4
#  Author: MingWei Dong
#  CruzID: mdong5
#
#  make                     makes FindComponenets
#  make GraphClient         makes GraphClient
#  make clean               removes binaries
#  make checkFind           tests FindComponenets for memory leaks on in4
#  make checkClient         tests GraphClient for memory leaks
#------------------------------------------------------------------------------

BASE_SOURCES   = Graph.c List.c
BASE_OBJECTS   = Graph.o List.o
HEADERS        = Graph.h List.h
COMPILE        = gcc -c -std=c11 -Wall -g
LINK           = gcc -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

FindComponents : FindComponents.o $(BASE_OBJECTS)
	$(LINK) FindComponents FindComponents.o $(BASE_OBJECTS)

GraphClient : GraphClient.o $(BASE_OBJECTS)
	$(LINK) GraphClient GraphClient.o $(BASE_OBJECTS)

FindComponents.o : FindComponents.c $(HEADERS)
	$(COMPILE) FindComponents.c

GraphClient.o : GraphClient.c $(HEADERS)
	$(COMPILE) GraphClient.c

$(BASE_OBJECTS) : $(BASE_SOURCES) $(HEADERS)
	$(COMPILE) $(BASE_SOURCES)

test : GraphTest.o $(BASE_OBJECTS)
	$(LINK) test GraphTest.o $(BASE_OBJECTS)

GraphTest.o : GraphTest.c $(HEADERS)
	$(COMPILE) GraphTest.c

clean :
	$(REMOVE) FindComponents GraphClient FindComponents.o GraphClient.o $(BASE_OBJECTS) test GraphTest.o out1 out2 out3 out4 out5 out6 out7
	rm -f *.txt *.sh

checkFind : FindComponenets
	$(MEMCHECK) FindComponenets in3 junk3

checkClient : GraphClient
	$(MEMCHECK) 
	
memcheck :
	make
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -v ./FindComponents in4 out4

memcheck1 :
	make GraphClient
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -v ./GraphClient

memcheck2 :
	make test
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -v ./test

grade : 
	curl https://raw.githubusercontent.com/houi-lin/cse101-pt.s20/master/pa4/pa4.sh > pa4.sh
	chmod +x pa4.sh
	./pa4.sh