//-----------------------------------------------------------------------------
// Graph.c
// Implementation file for Graph ADT
// Programming assignment 4
// Author: MingWei Dong
// CruzID: mdong5
//-----------------------------------------------------------------------------

#include "Graph.h"

/****** Private type definitions ******/
typedef struct GraphObj
{
    List *neighborsOf; // list of neighbors of [n th] element in the Graph.
    char *colorOf;     // states of color for the element at ith index
    int *parent;       // An array of ints whose nth element is the parent of vertex n.
    int *distance;     // An array of ints whose nth element is the distance from the (most recent) source to vertex n
    int *discover;     // the time of nth vertex be founded
    int *finish;       // the time of leaving the visit for nth vertex
    int order;         //  the field storing the n number of vertices
    int size;          // the field storing the number of edges
    int source;        // the label of the vertex that was most recently used as source for BFS
} GraphObj;

enum ColorStateFlags
{
    WHITE = 0x00,
    BLACK = 0x01,
    GRAY = 0x02
};

void insertListWithSort(List L, int n);
void visit(Graph G, int u, __uint64_t *time);
void sortByFinish(Graph G, List L);

/******* Constructors-Destructors *******/
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
    new->discover = calloc((n + 1), sizeof(int));
    new->finish = calloc((n + 1), sizeof(int));
    for (i = 0; i < n + 1; i++)
    {
        new->distance[i] = INF;
        new->discover[i] = UNDEF;
        new->finish[i] = UNDEF;
    }
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
    free(G->discover);
    free(G->finish);
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

int getDiscover(Graph G, int u)
{
    if (G == NULL || G->discover == NULL)
    {
        fprintf(stderr, "USAGE: getDiscover() called on non-correctly initialized Graph object\n");
        exit(EXIT_FAILURE);
    }
    return G->discover[u];
}

int getFinish(Graph G, int u)
{
    if (G == NULL || G->finish == NULL)
    {
        fprintf(stderr, "USAGE: getFinish() called on non-correctly initialized Graph object\n");
        exit(EXIT_FAILURE);
    }
    return G->finish[u];
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
            G->colorOf[i] = WHITE;
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
        G->colorOf[i] = WHITE;
        G->distance[i] = INF;
        G->parent[i] = NIL;
    }
    // mark up the sourse of searching
    G->colorOf[s] = BLACK;
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
                if (G->colorOf[get(pending)] == WHITE)
                {
                    append(queue, get(pending));
                    G->colorOf[get(pending)] = BLACK;
                    G->parent[get(pending)] = G->source;
                    G->distance[get(pending)] = G->distance[G->source] + 1;
                }
            }
        }
        deleteFront(queue);
    }
    freeList(&queue);
}

void DFS(Graph G, List S)
{
    if (G == NULL)
    {
        fprintf(stderr, "Graph Error: calling getSource() on NULL Graph reference\n");
        exit(EXIT_FAILURE);
    }
    if (S == NULL)
    {
        fprintf(stderr, "List Error: calling getSource() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(S) != getOrder(G))
    {
        fprintf(stderr, "List Error: calling getSource() on inconsistent List reference\n");
        exit(EXIT_FAILURE);
    }

    __uint64_t timestamp = 0;

    for (moveFront(S); index(S) >= 0; moveNext(S))
    {
        G->colorOf[get(S)] = WHITE;
        G->discover[get(S)] = UNDEF;
        G->finish[get(S)] = UNDEF;
    }
    for (moveFront(S); index(S) >= 0; moveNext(S))
    {
        if (G->colorOf[get(S)] == WHITE)
        {
            // printf("attempt to vist vertex %d: \n", get(S));
            visit(G, get(S), &timestamp);
        }
    }
    sortByFinish(G, S);
}

/*** Other operations ***/
Graph copyGraph(Graph G)
{
    if (G == NULL)
    {
        printf("copyGraph() Error: Called on NULL graph");
        exit(EXIT_FAILURE);
    }

    Graph new = newGraph(getOrder(G));

    int i;
    for (i = 1; i <= getOrder(G); i++)
    {
        new->neighborsOf[i] = copyList(G->neighborsOf[i]);
        // for (moveFront(G->neighborsOf[i]); index(G->neighborsOf[i]) >= 0; moveNext(G->neighborsOf[i]))
        //     addArc(new, i, get(G->neighborsOf[i]));
        new->colorOf[i] = G->colorOf[i];
        new->discover[i] = G->discover[i];
        new->finish[i] = G->finish[i];
        new->parent[i] = G->parent[i];
        new->source = G->source;
    }

    return new;
}

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

Graph transpose(Graph G)
{
    if (G == NULL)
    {
        printf("Graph Error: calling transpose on a null graph Reference\n");
        exit(EXIT_FAILURE);
    }

    Graph temp = newGraph(getOrder(G));
    for (int i = 1; i <= getOrder(G); i++)
        for (moveFront(G->neighborsOf[i]); index(G->neighborsOf[i]) >= 0; moveNext(G->neighborsOf[i]))
            addArc(temp, get(G->neighborsOf[i]), i);
    return temp;
}

/*** Private functions ***/

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

void visit(Graph G, int u, __uint64_t *time)
{
    *time += 1;
    G->discover[u] = *time;
    G->colorOf[u] = GRAY;
    // printf("%d discovered\n", u);
    // printf("Entering adjacency list... \n");
    for (moveFront(G->neighborsOf[u]); index(G->neighborsOf[u]) >= 0; moveNext(G->neighborsOf[u]))
    {
        if (G->colorOf[get(G->neighborsOf[u])] == WHITE)
        {
            // printf("undiscovered vertex %d found\n", get(G->neighborsOf[u]));
            G->parent[get(G->neighborsOf[u])] = u;
            visit(G, get(G->neighborsOf[u]), time);
        }
    }
    G->colorOf[u] = BLACK;
    *time += 1;
    G->finish[u] = *time;
    // printf("visit to %d finished\n", u);
}

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sortByFinish(Graph G, List L)
{

    int *queue = calloc(getOrder(G), sizeof(int));
    int i, j, min_idx;

    for (moveFront(L), i = 0; index(L) >= 0; moveNext(L), i++)
    {
        queue[i] = get(L);
    }

    clear(L);

    // One by one move boundary of unsorted subarray
    for (i = 0; i < getOrder(G) - 1; i++)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i + 1; j < getOrder(G); j++)
            if (getFinish(G, queue[j]) < getFinish(G, queue[min_idx]))
                min_idx = j;

        // Swap the found minimum element with the first element
        swap(&queue[min_idx], &queue[i]);
    }
    for (i = 0; i < getOrder(G); i++)
    {
        prepend(L, queue[i]);
    }
    // printf("\n");
    free(queue);
}

void selectionSort(int arr[], int n)
{
    int i, j, min_idx;

    // One by one move boundary of unsorted subarray
    for (i = 0; i < n - 1; i++)
    {
        // Find the minimum element in unsorted array
        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;

        // Swap the found minimum element with the first element
        swap(&arr[min_idx], &arr[i]);
    }
}
