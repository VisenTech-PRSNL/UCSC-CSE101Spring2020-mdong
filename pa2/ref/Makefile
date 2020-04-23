#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 2
#
#       make                   makes Arithmetic
#       make BigIntegerTest        makes BigIntegerTest
#------------------------------------------------------------------------------

Arithmetic : Arithmetic.o List.o BigInteger.o
	gcc -o Arithmetic Arithmetic.o List.o BigInteger.o

Arithmetic.o : Arithmetic.c List.h
	gcc -c -std=c99 -Wall Arithmetic.c

BigIntegerTest: BigIntegerTest.o List.o BigInteger.o
	gcc -o BigIntegerTest BigIntegerTest.o List.o BigInteger.o

BigIntegerTest.o : BigIntegerTest.c BigInteger.h List.h
	gcc -c -std=c99 -Wall BigIntegerTest.c

test : List 

List.o : List.c List.h
	gcc -c -std=c99 -Wall List.c

List : List.o ListTest.o
	gcc -o Test List.o ListTest.o

ListTest.o : ListTest.c List.h
	gcc -c -std=c99 -Wall ListTest.c

clean :
	rm -f Arithmetic BigIntegerTest Arithmetic.o BigIntegerTest.o List.o ListTest.o Test out1 out2 out3
	rm -f *.txt *.sh

memcheck :
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./Arithmetic
	
memcheck1 :
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -v ./Test

memcheck2 :
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -v ./BigIntegerTest

grade : 
	curl https://raw.githubusercontent.com/houi-lin/cse101-pt.s20/master/pa2/pa2.sh > pa2.sh
	chmod +x pa2.sh
	./pa2.sh

