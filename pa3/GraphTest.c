//-----------------------------------------------------------------------------
// GraphTest.c
// technical test file for Graph ADT
// Programming assignment 3
// Author: MingWei Dong
// CruzID: mdong5
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

void showGraph(Graph G);
int main()
{
	int n = 10;
	__uint8_t i = 0;
	Graph G = newGraph(n);
	printf("Distance from 8 to BFS source is %d\n", getDist(G, 8));
	addEdge(G, 1, 2);
	addEdge(G, 1, 3);
	addEdge(G, 2, 4);
	addEdge(G, 2, 5);
	addEdge(G, 2, 6);
	addEdge(G, 3, 4);
	addEdge(G, 4, 5);
	addEdge(G, 5, 6);
	addEdge(G, 6, 7);
	addEdge(G, 7, 8);
	printGraph(stdout, G);
	printf("getOrder: %d\n", getOrder(G));
	printf("getSize: %d\n", getSize(G));

	BFS(G, 1);
	//	BFS(G, 2);
	//	BFS(G, 3);

	printf("getSource: %d\n", getSource(G));
	printf("getParent of 8 : %d\n", getParent(G, 8));
	printf("getDist of 8: %d\n", getDist(G, 8));
	printf("========================\n");
	List L = newList();
	getPath(L, G, 8);
	for (moveFront(L); index(L) >= 0; moveNext(L))
	{
		printf("%d ", get(L));
	}
	printf("\n");
	showGraph(G);
	puts("-----MAKENULL TEST-----");
	makeNull(G);
	freeGraph(&G);
	puts("-----PARENT TEST-----");
	G = newGraph(100);
	for (i = 1; i <= 100; i++)
		if (getParent(G, i) != NIL)
			puts("test 1");
	addArc(G, 64, 4);
	addArc(G, 64, 3);
	addArc(G, 42, 2);
	addArc(G, 2, 64);
	addArc(G, 4, 2);
	addArc(G, 3, 42);
	BFS(G, 42);
	if (getParent(G, 42) != NIL)
		puts("test 2");
	if (getParent(G, 2) != 42)
		puts("test 3");
	if (getParent(G, 8) != NIL)
		puts("test 4");

	puts("-----PATH TEST-----");
	freeGraph(&G);
	G = newGraph(100);
	freeList(&L);
	L = newList();
	List C = newList();
	addArc(G, 64, 4);
	addArc(G, 64, 3);
	addArc(G, 42, 2);
	addArc(G, 2, 64);
	addArc(G, 4, 2);
	addArc(G, 3, 42);
	BFS(G, 3);
	getPath(L, G, 64);
	append(C, 3);
	append(C, 42);
	append(C, 2);
	append(C, 64);

	printf("Path found is: ");
	printList(stdout, L);
	printf("\n");
	printf("List C is: ");
	printList(stdout, C);
	printf("\n");

	if (!equals(L, C))
		puts("test 1");
	moveFront(L);
	BFS(G, 2);
	getPath(L, G, 2);
	append(C, 2);

	printf("Path found is: ");
	printList(stdout, L);
	printf("\n");
	printf("List C is: ");
	printList(stdout, C);
	printf("\n");

	if (!equals(L, C))
		puts("test 2");

	printf("Path found is: ");
	printList(stdout, L);
	printf("\n");
	printf("List C is: ");
	printList(stdout, C);
	printf("\n");

	getPath(L, G, 99);
	if (equals(L, C))
		puts("test 3");
	clear(L);
	clear(C);
	append(C, NIL);
	BFS(G, 99);
	getPath(L, G, 2);

	printf("Path found is: ");
	printList(stdout, L);
	printf("\n");
	printf("List C is: ");
	printList(stdout, C);
	printf("\n");

	if (!equals(C, L))
		puts("test 4");

	freeGraph(&G);
	freeList(&L);
	freeList(&C);
	return 0;
}

void showGraph(Graph G)
{
	printf("order:\t%d\n", getOrder(G));
	printf("size:\t%d\n", getSize(G));
	printf("source:\t%d\n", getSource(G));
	printf("parent:\t");
	for (int i = 1; i <= getOrder(G); i++)
		printf("%d ", getParent(G, i));
	printf("\n");
	printf("distance:\t");
	for (int i = 1; i <= getOrder(G); i++)
		printf("%d ", getDist(G, i));
	printf("\n");
}