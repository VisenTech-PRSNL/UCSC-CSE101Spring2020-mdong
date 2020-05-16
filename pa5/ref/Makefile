main : main.o
	gcc -std=c11 -Wall -o main main.o

main.o : 
	gcc -std=c11 -Wall -c -g main.c

clean : 
	rm -f main main.o

check : 
	valgrind --leak-check=full ./main