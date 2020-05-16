//-----------------------------------------------------------------------------
// GraphTest.c
// technical test file for Graph ADT
// Programming assignment 4
// Author: MingWei Dong
// CruzID: mdong5
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

void showGraph(Graph G, List L)
{
	printf("Sequential controller List reference: \n");
	printList(stdout, L);
	printf("\n");
	printf("vertex#  Parent  Discover  Finish\n");
	for (int i = 1; i <= getOrder(G); i++)
	{
		printf("% 7d  % 6d  % 8d  % 6d\n",
			   i, getParent(G, i), getDiscover(G, i), getFinish(G, i));
	}
}

int main()
{
	int n = 6;
	__uint8_t i = 0;
	Graph G = newGraph(n);
	Graph Gt;
	List IN_OUT_PARA = newList();
	for (i = 1; i <= n; i++)
		append(IN_OUT_PARA, i);

	// addArc(G, 1, 2);
	// addArc(G, 2, 3);
	// addArc(G, 2, 5);
	// addArc(G, 2, 6);
	// addArc(G, 3, 4);
	// addArc(G, 3, 7);
	// addArc(G, 4, 3);
	// addArc(G, 4, 8);
	// addArc(G, 5, 1);
	// addArc(G, 5, 6);
	// addArc(G, 6, 7);
	// addArc(G, 7, 6);
	// addArc(G, 7, 8);
	// addArc(G, 8, 8);
	addArc(G, 1, 2);
	addArc(G, 1, 4);
	addArc(G, 2, 3);
	addArc(G, 2, 5);
	addArc(G, 2, 6);
	addArc(G, 5, 3);
	addArc(G, 5, 4);
	addArc(G, 5, 6);
	printf("Graph G adjacents: \n");
	printGraph(stdout, G);
	Gt = transpose(G);
	printf("Graph G transposed adjacents: \n");
	printGraph(stdout, Gt);

	showGraph(G, IN_OUT_PARA);
	// printf("getOrder: %d\n", getOrder(G));
	// printf("getSize: %d\n", getSize(G));

	DFS(G, IN_OUT_PARA);
	printf("Graph G fields: \n");
	showGraph(G, IN_OUT_PARA);

	DFS(Gt, IN_OUT_PARA);
	printf("Graph transposed G fields: \n");
	showGraph(Gt, IN_OUT_PARA);

	int componentCounter = 0;
	for (moveFront(IN_OUT_PARA); index(IN_OUT_PARA) >= 0; moveNext(IN_OUT_PARA))
	{
		printf("%d: %d\n",  get(IN_OUT_PARA), getParent(Gt, get(IN_OUT_PARA)));
		if (getParent(Gt, get(IN_OUT_PARA)) == 0)
			componentCounter += 1;
	}
	if (componentCounter > 0)
    {
        printf("G contains %d strongly connected components:\n", componentCounter);
    }

	freeList(&IN_OUT_PARA);
	freeGraph(&G);
	freeGraph(&Gt);
}