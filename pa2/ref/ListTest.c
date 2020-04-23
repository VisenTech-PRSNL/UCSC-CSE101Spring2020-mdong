#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <signal.h>
#include <setjmp.h>
#include "List.h"

int main()
{
    int i=0;
	puts("----------TEST START----------");
    List A = newList();
    for(i=1; i<=20; i++)
      	append(A,i);
    printList(stdout,A);
    printf("\n");
    moveFront(A);
    moveNext(A);
	moveNext(A);
	moveNext(A);
	set(A,-999);
	printList(stdout,A);
    printf("\n");
    puts("----------TEST END----------");
    return 0;      
}