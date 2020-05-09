//-----------------------------------------------------------------------------
// Graph.h
// Header file for the Graph ADT in C
// Programming assignment 4
// Author: MingWei Dong
// CruzID: mdong5
//-----------------------------------------------------------------------------
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "List.h"

#ifndef _GRAPH_H_INCLUDE_
#define _GRAPH_H_INCLUDE_
#define NIL 0
#define INF -1
#define UNDEF -1
// Exported type --------------------------------------------------------------
typedef struct GraphObj *Graph;
/******* Constructors-Destructors *******/
// Function newGraph() returns a Graph pointing to a newly created GraphObj representing a graph having n vertices and no edges
Graph newGraph(int n);
// Function freeGraph() frees all dynamic memory associated with the Graph *pG, then sets the handle *pG to NULL
void freeGraph(Graph *pG);

/******* Access functions *******/
// Functions getOrder() and getSize() return the corresponding field values, and getSource() returns the source vertex most recently used in function BFS(), or NIL if BFS() has not yet been called
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
// Functions getParent(), getDist() and getPath() all have the precondition 1 <= u <= getOrder(G)
//  Function getParent() will return the parent of vertex u in the BreadthFirst tree created by BFS(), or NIL if BFS() has not yet been called
int getParent(Graph G, int u);
// Function getDist() returns the distance from the most recent BFS source to vertex u, or INF if BFS() has not yet been called
int getDist(Graph G, int u);
// Function getPath() appends to the List L the vertices of a shortest path in G from source to u, or appends to L the value NIL if no such path exists
// getPath() has the precondition getSource(G)!=NIL, so BFS() must be called before getPath().
void getPath(List L, Graph G, int u);

int getDiscover(Graph G, int u); /* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u);   /* Pre: 1<=u<=n=getOrder(G) */

/*** Manipulation procedures ***/
// Function makeNull() deletes all edges of G, restoring it to its original (no edge) state. (This is called a null graph in graph theory literature)
void makeNull(Graph G);
// addEdge() inserts a new edge joining u to v, i.e. u is added to the adjacency List of v, and v to the adjacency List of u. Your program is required to maintain these lists in sorted order by increasing labels
void addEdge(Graph G, int u, int v);
// addArc() inserts a new directed edge from u to v, i.e. v is added to the adjacency List of u (but not u to the adjacency List of v). Both addEdge() and addArc() have the precondition that their two int arguments must lie in the range 1 to getOrder(G).
void addArc(Graph G, int u, int v);
// Function BFS() runs the BFS algorithm on the Graph G with source s, setting the color, distance, parent, and source fields of G accordingly
void BFS(Graph G, int s);
void DFS(Graph G, List S); /* Pre: length(S)==getOrder(G) */

/*** Other operations ***/
// function printGraph() prints the adjacency list representation of G to the file pointed to by out
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE *out, Graph G);

#endif