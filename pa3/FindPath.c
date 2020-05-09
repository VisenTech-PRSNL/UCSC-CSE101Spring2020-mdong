//------------------------------------------------------
// FindPath.c
// Programming assignment 3
// author MingWei Dong
// cruzID mdong5
// the client for Graph ADT
//------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Graph.h"
#include "List.h"

void calculateDistance(FILE *out, Graph G, int x, int y);
void printPath(FILE *out, List L);

int main(int argc, char *argv[])
{
    int i, j, vertices;
    int lineLength;
    // int *indexArray;
    char buffer[20], param1[10], param2[10];
    // char *buffer;
    FILE *in, *out;
    // -------------condition check--------------
    if (argc != 3)
    {
        fprintf(stderr, "USAGE: ./<Program name> + <input file name> + <out file name>\n");
        exit(EXIT_FAILURE);
    }

    // open input file for reading
    if ((in = fopen(argv[1], "r")) == NULL)
    {
        fprintf(stderr, "Unable to read from file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // open output file for writing
    if ((out = fopen(argv[2], "w")) == NULL)
    {
        fprintf(stderr, "Unable to write to file %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    // read in numbers of vertices
    fgets(buffer, 20, in);
    vertices = atoi(buffer);
    // printf("there will be %d vertices in the graph\n", vertices);
    memset(buffer, '\0', sizeof(buffer));
    memset(param1, '\0', sizeof(buffer));
    memset(param2, '\0', sizeof(buffer));
    // printf("buf: %s\n", buffer);

    Graph G = newGraph(vertices);
    while (fgets(buffer, 20, in) != NULL)
    {
        if (strcmp(buffer, "0 0") == 0 || strcmp(buffer, "0 0\n") == 0)
            break;
        lineLength = strlen(buffer);
        // printf("this line is %s\n", buffer);
        // printf("this line length %d\n", lineLength);
        for (i = 0; i < lineLength; i++) // parse first parameter for addEdge
        {
            // printf("checking on char \"%c\" \n", buffer[i]);
            if (buffer[i] != ' ')
            {
                param1[i] = buffer[i];
            }
            else
                break;
        }
        // printf("first parameter length %d\n", strlen(param1));
        for (i = strlen(param1) + 1, j = 0;
             i < lineLength && j < (lineLength - strlen(param1));
             i++, j++) // parse first parameter for addEdge
        {

            // printf("checking on char \"%c\" \n", buffer[i]);
            if (buffer[i] != ' ' && buffer[i] != '\n')
            {
                param2[j] = buffer[i];
                // printf("pend %c\n", param2[j]);
            }
            else
                break;
        }
        // printf("second parameter length %d\n", strlen(param2));
        // printf("param1: %s, param2: %s\n", param1, param2);
        addEdge(G, atoi(param1), atoi(param2));
        memset(buffer, '\0', sizeof(buffer));
        memset(param1, '\0', sizeof(buffer));
        memset(param2, '\0', sizeof(buffer));
    }
    printGraph(out, G);
    fprintf(out, "\n");

    memset(buffer, '\0', sizeof(buffer));
    memset(param1, '\0', sizeof(buffer));
    memset(param2, '\0', sizeof(buffer));
    while (fgets(buffer, 20, in) != NULL) // this loop is identical purpose to the one above
    {
        if (strcmp(buffer, "0 0") == 0 || strcmp(buffer, "0 0\n") == 0)
            break;
        lineLength = strlen(buffer);
        for (i = 0; i < lineLength; i++)
        {
            if (buffer[i] != ' ')
                param1[i] = buffer[i];
            else
                break;
        }
        for (i = strlen(param1) + 1, j = 0; i < lineLength && j < (lineLength - strlen(param1)); i++, j++)
        {
            if (buffer[i] != ' ' && buffer[i] != '\n')
                param2[j] = buffer[i];
            else
                break;
        }
        calculateDistance(out, G, atoi(param1), atoi(param2));
        memset(buffer, '\0', sizeof(buffer));
        memset(param1, '\0', sizeof(buffer));
        memset(param2, '\0', sizeof(buffer));
    }
    fclose(in);
    fclose(out);
    freeGraph(&G);
}

void calculateDistance(FILE *out, Graph G, int x, int y)
{
    List L = newList();
    BFS(G, x);
    getPath(L, G, y);
    if (length(L) >= 1 && front(L) != NIL)
    {
        fprintf(out, "The distance from %d to %d is %d\n", x, y, length(L) - 1);
        fprintf(out, "A shortest %d-%d path is: ", x, y);
        printPath(out, L);
        fprintf(out, "\n");
    }
    else
    {
        fprintf(out, "The distance from %d to %d is infinity\n", x, y);
        fprintf(out, "No %d-%d path exists\n", x, y);
    }
    freeList(&L);
}

void printPath(FILE *out, List L)
{
    for (moveFront(L); index(L) >= 0; moveNext(L))
    {
        fprintf(out, "%d ", get(L));
    }
    fprintf(out, "\n");
}