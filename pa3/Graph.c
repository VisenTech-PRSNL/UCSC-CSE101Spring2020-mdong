//-----------------------------------------------------------------------------
// Graph.c
// Implementation file for Graph ADT
// Programming assignment 3
// Author: MingWei Dong
// CruzID: mdong5
//-----------------------------------------------------------------------------

#include "Graph.h"

typedef struct GraphObj
{
    List *neighborsOf; // list of neighbors of [ith] element in the Graph.
    char *colorOf;     // states of color for the element at ith index
    int *parent;       // An array of ints whose ith element is the parent of vertex i.
    int *distance;     // An array of ints whose ith element is the distance from the (most recent) source to vertex i
    int order;         //  the field storing the number of vertices
    int size;          // the field storing the number of edges
    int source;        // the label of the vertex that was most recently used as source for BFS

} GraphObj;

enum ColorStateFlags
{
    NOT_USED = 0x0,
    USED = 0x1
};
void insertListWithSort(List L, int n);

Graph newGraph(int n)
{
    int i;
    Graph new = malloc(sizeof(GraphObj));
    new->neighborsOf = malloc((n + 1) * sizeof(List));
    new->neighborsOf[0] = NULL;
    for (i = 1; i < n + 1; i++)
        new->neighborsOf[i] = newList();
    new->colorOf = calloc((n + 1), sizeof(char));
    new->parent = calloc((n + 1), sizeof(int));
    new->parent[0] = NIL;
    new->distance = calloc((n + 1), sizeof(int));
    for (i = 0; i < n + 1; i++)
        new->distance[i] = INF;
    new->order = n;
    new->size = 0;
    new->source = NIL;
    return new;
}
void freeGraph(Graph *pG)
{
    int i;
    assert((pG != NULL && (*pG) != NULL) && "USAGE: copy() call on uninitalized BigInteger");
    Graph G = *pG;
    for (i = 0; i < G->order + 1; i++)
    {
        if (&((G->neighborsOf)[i]) != NULL)
            freeList(&((G->neighborsOf)[i]));
    }
    free(G->neighborsOf);
    free(G->distance);
    free(G->colorOf);
    free(G->parent);
    free(*pG);
    *pG = NULL;
}
/*** Access functions ***/
int getOrder(Graph G)
{
    assert(G != NULL);
    return G->order;
}
int getSize(Graph G)
{
    assert(G != NULL);
    return G->size;
}
int getSource(Graph G)
{
    assert(G != NULL);
    return G->source;
}
int getParent(Graph G, int u)
{
    assert(G != NULL);
    if (u >= 1 && u <= getOrder(G))
        return (G->parent)[u];
    else
        return NIL;
}
int getDist(Graph G, int u)
{
    assert(G != NULL && u >= 1 && u <= getOrder(G));
    return (G->distance)[u];
}
void getPath(List L, Graph G, int u)
{
    if (getSource(G) != NIL && u >= 1 && u <= getOrder(G))
    {
        int parent;
        if (getDist(G, u) > 0) // if u has found by BFS
        {
            append(L, u);
            parent = G->parent[u];
            while (parent > 0)
            {
                prepend(L, parent);
                parent = G->parent[parent];
            }
        }
        else if (getDist(G, u) == 0) // if u is BFS source itself
        {
            append(L, u);
        }
        else
        {
            append(L, NIL);
        }
    }
}

/*** Manipulation procedures ***/
void makeNull(Graph G)
{
    int i;
    for (i = 0; i < G->order + 1; i++)
    {
        if ((G->neighborsOf)[i] != NULL)
        {
            clear(G->neighborsOf[i]);
            G->distance[i] = INF;
            G->colorOf[i] = NOT_USED;
            G->parent[i] = NIL;
        }
    }
}
void addEdge(Graph G, int u, int v)
{
    assert(u >= 1 && u <= getOrder(G) && v >= 1 && v <= getOrder(G));
    // printf("adding %d to [%d]\n", v, u);
    insertListWithSort((G->neighborsOf)[u], v);
    // printf("adding %d to [%d]\n", u, v);
    insertListWithSort((G->neighborsOf)[v], u);
    G->size += 1;
}
void addArc(Graph G, int u, int v)
{
    assert(u >= 1 && u <= getOrder(G) && v >= 1 && v <= getOrder(G));
    insertListWithSort((G->neighborsOf)[u], v);
    G->size += 1;
}
void BFS(Graph G, int s)
{

    int i;
    List pending;
    for (i = 1; i <= G->order; i++) // initialize graph information fields
    {
        G->colorOf[i] = NOT_USED;
        G->distance[i] = INF;
        G->parent[i] = NIL;
    }
    // mark up the sourse of searching
    G->colorOf[s] = USED;
    G->distance[s] = 0;
    G->parent[s] = 0;
    G->source = s;

    List queue = newList();
    append(queue, s);
    moveFront(queue);

    while (length(queue) > 0)
    {
        G->source = front(queue);
        pending = G->neighborsOf[G->source];
        if (pending != NULL)
        {
            for (moveFront(pending); index(pending) >= 0; moveNext(pending))
            {
                if (G->colorOf[get(pending)] == NOT_USED)
                {
                    append(queue, get(pending));
                    G->colorOf[get(pending)] = USED;
                    G->parent[get(pending)] = G->source;
                    G->distance[get(pending)] = G->distance[G->source] + 1;
                }
            }
        }
        deleteFront(queue);
    }
    freeList(&queue);
}
/*** Other operations ***/
void printGraph(FILE *out, Graph G)
{
    int i;
    for (i = 1; i <= G->order; i++)
    {
        fprintf(out, "%d: ", i);
        printList(out, (G->neighborsOf)[i]);
        fprintf(out, "\n");
    }
}

void insertListWithSort(List L, int n)
{
    int targetIndex = -1;
    for (moveFront(L); index(L) >= NIL; moveNext(L))
    {
        if (n > get(L))
        {
            targetIndex = index(L);
        }
    }
    if (targetIndex == -1)
    {
        prepend(L, n); // pending vertex n is smaller than all existing elements
    }
    else
    {
        for (moveFront(L); index(L) >= 0; moveNext(L))
        {
            if (index(L) == targetIndex)
            {
                insertAfter(L, n); // pending vertex n is larger than target element
                break;
            }
        }
    }
}