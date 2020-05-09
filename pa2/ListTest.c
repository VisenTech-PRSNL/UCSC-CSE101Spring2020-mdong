/**********************************************
 * 
 *  ListTest.c
 *  several hard-coded test for List.c
 *  Author_ID: mdong5
 * 
**********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <signal.h>
#include <setjmp.h>
#include "List.h"

int main()
{
    puts("----------TEST START----------");
    List A = newList();
    List B = newList();
    prepend(B, 1);
    prepend(B, 2);
    append(A, 3);
    append(A, 4);
    printf("1. the cursor index in A is at %ld\n", listIndex(A));
    printf("2. The list A has %ld elements\n", length(A));
    printf("A: ");
    printList(stdout, A);
    printf("\n");
    printf("B: ");
    printList(stdout, B);
    printf("\n");
    moveFront(A);
    moveNext(A);
    printf("3. the cursor index in A is at %ld\n", listIndex(A));
    printf("4. the cursor in A is pointing to the data of %ld\n", get(A));
    prepend(A, 2);
    prepend(A, 1);
    printf("A: ");
    printList(stdout, A);
    printf("\n");
    printf("5. the cursor index in A is at %ld\n", listIndex(A));
    printf("6. the cursor in A is pointing to the data of %ld\n", get(A));
    moveFront(A);
    printf("7. the cursor in A is pointing to the data of %ld\n", get(A));
    printf("A: ");
    printList(stdout, A);
    printf("\n");
    printf("B: ");
    printList(stdout, B);
    printf("\n");
    printf("8. The list A has %ld elements\n", length(A));
    printf("9. The list B has %ld elements\n", length(B));
    deleteFront(A);
    printf("10. The list A has %ld elements\n", length(A));
    deleteBack(A);
    printf("11. The list A has %ld elements\n", length(A));
    printf("A: ");
    printList(stdout, A);
    printf("\n");
    clear(A);
    append(A, 5);
    append(A, 6);
    append(A, 7);
    printf("A: ");
    printList(stdout, A);
    printf("\n");
    printf("12. The list has %ld elements\n", length(A));
    printf("13. the front element is %ld\n", front(A));
    printf("14. the back element is %ld\n", back(A));
    printf("A: ");
    printList(stdout, A);
    printf("\n");
    printf("15. A and B are equal?: %s\n", listEquals(A, B) == true ? "true" : "false");
    moveFront(B);
    insertBefore(B, 4);
    insertBefore(B, 3);
    printf("B: ");
    printList(stdout, B);
    printf("\n");
    List C = copyList(A);
    printf("16. A and C are equal?: %s\n", listEquals(A, C) == true ? "true" : "false");
    // printf("C: ");
    // printList(stdout, C);
    freeList(&A);
    freeList(&B);
    freeList(&C);

    A = newList();
    append(A, 1);
    append(A, 2);
    printf("17. length: %ld\n", length(A));
    moveFront(A);
    delete (A);
    printf("18. length: %ld\n", length(A));
    append(A, 3);
    append(A, 5);
    printf("19. length: %ld\n", length(A));
    moveFront(A);
    insertAfter(A, 12);
    printf("20. length: %ld\n", length(A));
    delete (A);
    printf("21. length: %ld\n", length(A));
    printList(stdout, A);
    printf("\n");
    printf("22. length: %ld\n", length(A));
    freeList(&A);

    A = newList();
    C = copyList(A);
    printf("23. A and C are equal?: %s\n", listEquals(A, C) == true ? "true" : "false");
    freeList(&C);
    puts("----------TEST END----------");
}