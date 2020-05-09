#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

void printStringArray(FILE *out, char **array, List L, int count);

int main(int argc, char *argv[])
{
    int count = 0, i, j;
    int *lineLength;
    int *indexArray;
    char c = '0';
    char **input;
    // char *buffer;
    FILE *in, *out;
    // -------------condition check--------------
    if (argc <= 1)
    {
        fprintf(stderr, "USAGE: ./<Program name> + <input file name>\n");
        exit(EXIT_FAILURE);
    }

    // open input file for reading
    if ((in = fopen(argv[1], "r")) == NULL)
    {
        printf("Unable to read from file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // open output file for writing
    if ((out = fopen(argv[2], "w")) == NULL)
    {
        printf("Unable to write to file %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    // read in m lines from input file
    for (c = getc(in); c != EOF; c = getc(in))
        if (c == '\n') // Increment count if this character is newline
            count = count + 1;

    // printf("The input file has %d words\n", count);
    rewind(in);

    // read in the length for each line
    lineLength = calloc(count, sizeof(int));
    i = 0;
    for (c = getc(in); c != EOF; c = getc(in))
    {
        lineLength[i] += 1;
        if (c == '\n')
        { // Increment count if this character is newline
            // printf("line %d has %d cahracters\n", i, lineLength[i]);
            i = i + 1;
        }
    }
    rewind(in);

    // integrate List according to line counts
    // List output = newList();
    // for (i = 0; i < count; i++)
    // {
    //     append(output, i);
    // }
    // printList(stdout, output);
    // printf("\n");

    indexArray = calloc(count, sizeof(int));
    for (i = 0; i < count; i++)
    {
        indexArray[i] = i;
    }
    for (i = 0; i < count; i++)
    {
        // printf("%d ", indexArray[i]);
    }
    // printf("\n");
    List output = newList();

    // allocate backup storage for input file by using the length obtained earlier
    input = malloc((count + 1) * sizeof(char *));
    c = 0;
    for (i = 0; i < count + 1; i++)
    {
        if (i < count)
        {
            input[i] = calloc(lineLength[i] + 1, sizeof(char));
            // while (c != '\n')
            // {
            //     c = getc(in);
            // }
            fgets(input[i], lineLength[i] + 1, in);
            // printf("%s is stored\n", input[i]);
        }
        else if (i == count)
            input[i] = NULL;
    }

    int key;
    for (i = 1; i < count; i++)
    {
        key = indexArray[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are 
          greater than key, to one position ahead 
          of their current position */
        while (j >= 0 && strcmp(input[indexArray[j]], input[key]) > 0)
        {
            indexArray[j + 1] = indexArray[j];
            j = j - 1;
        }
        indexArray[j + 1] = key;
    }
    for (i = 0; i < count; i++)
    {
        // printf("%d ", indexArray[i]);
        append(output, indexArray[i]);
    }
    // printf("\n");
    printStringArray(out, input, output, count);

    for (i = 0; i <= count; i++)
    {
        if (input[i] != NULL)
        {
            free(input[i]);
            input[i] = NULL;
        }
    }
    free(input);
    free(lineLength);
    free(indexArray);
    lineLength = NULL;
    indexArray = NULL;
    input = NULL;
    fclose(in);
    fclose(out);
    freeList(&output);
}

void printStringArray(FILE *out, char **array, List L, int count)
{
    int i;
    moveFront(L);
    // for (i = 0; array[i] != NULL; i++)
    // {
    //     printf("%s", array[i]);
    // }
    for (i = 0; i < count; i++)
    {
        fprintf(out, "%s", array[get(L)]);
        // printf("%s", array[get(L)]);
        moveNext(L);
    }
}
