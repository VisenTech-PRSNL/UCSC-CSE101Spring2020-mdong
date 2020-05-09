#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 1
#
#       make                   makes Lex
#       make ListClient        makes ListClient
#------------------------------------------------------------------------------

Lex : Lex.o List.o
	gcc -o Lex Lex.o List.o

Lex.o : Lex.c List.h
	gcc -c -std=c99 -Wall Lex.c

ListClient: ListClient.o List.o
	gcc -o ListClient ListClient.o List.o

ListClient.o : ListClient.c List.h
	gcc -c -std=c99 -Wall ListClient.c

List.o : List.c List.h
	gcc -c -std=c99 -Wall List.c

test : List 
List : List.o ListTest.o
	gcc -o Test List.o ListTest.o

ListTest.o : ListTest.c List.h
	gcc -c -std=c99 -Wall ListTest.c

clean :
	rm -f Lex ListClient Lex.o ListClient.o List.o ListTest.o Test out1 out2 out3
	rm -f *.txt *.sh

memcheck :
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./Lex in2 out2
	

memcheck1 :
	valgrind --leak-check=full --show-leak-kinds=all ./Test

memcheck2 :
	valgrind --leak-check=full --show-leak-kinds=all ./ListClient

grade : 
	curl https://raw.githubusercontent.com/houi-lin/cse101-pt.s20/master/pa1/pa1.sh > pa1.sh
	chmod +x pa1.sh
	./pa1.sh
