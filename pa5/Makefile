#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 5
#
#  make                     makes Lex
#  make DictionaryClient    makes DictionaryClient
#  make test                make DictionaryTest
#  make clean               removes all binaries
#  make check1              checks DictionaryClient for memory leaks
#  make check2              checks Lex for memory leaks on in4
#  make check3              check DictionaryTest for memory leaks
#------------------------------------------------------------------------------

TOP              = Lex
TOP_OBJ          = $(TOP).o
TOP_SRC          = $(TOP).c
ADT              = Dictionary
TEST             = $(ADT)Client
TEST_OBJ         = $(TEST).o
TEST_SRC         = $(TEST).c
ADT_OBJ          = $(ADT).o
ADT_SRC          = $(ADT).c
ADT_HDR          = $(ADT).h
COMPILE          = gcc -std=c11 -Wall -c -g
LINK             = gcc -std=c11 -Wall -o
REMOVE           = rm -f
MEMCHECK         = valgrind --leak-check=full

$(TOP) : $(TOP_OBJ) $(ADT_OBJ)
	$(LINK) $(TOP) $(TOP_OBJ) $(ADT_OBJ)

$(TEST) : $(TEST_OBJ) $(ADT_OBJ)
	$(LINK) $(TEST) $(TEST_OBJ) $(ADT_OBJ)

$(TOP_OBJ) : $(TOP_SRC) $(ADT_HDR)
	$(COMPILE) $(TOP_SRC)

$(TEST_OBJ) : $(TEST_SRC) $(ADT_HDR)
	$(COMPILE) $(TEST_SRC)

$(ADT_OBJ) : $(ADT_SRC) $(ADT_HDR)
	$(COMPILE) $(ADT_SRC)

test  : DictionaryTest.o $(ADT_OBJ)
	$(LINK) DictionaryTest DictionaryTest.o $(ADT_OBJ)

DictionaryTest.o : DictionaryTest.c $(ADT_HDR)
	$(COMPILE) DictionaryTest.c

clean :
	$(REMOVE) $(TOP) $(TOP_OBJ) $(TEST) $(TEST_OBJ) $(ADT_OBJ) DictionaryTest DictionaryTest.o out1 out2 out3 junk4 my3
	rm -f *.txt *.sh

check1 : $(TEST)
	$(MEMCHECK) ./$(TEST)

check2 : $(TOP)
	$(MEMCHECK) ./$(TOP) in4 junk4

check3 : 
	make test
	$(MEMCHECK) ./DictionaryTest

grade : 
	curl https://raw.githubusercontent.com/houi-lin/cse101-pt.s20/master/pa5/pa5.sh > pa5.sh
	chmod +x pa5.sh
	./pa5.sh