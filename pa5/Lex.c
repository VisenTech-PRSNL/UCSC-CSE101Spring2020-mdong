//-----------------------------------------------------------------------------
// Lex.c
// Lexicon is a list of words that belong to a particular language
// Top client for Dictionary ADT
// USAGE: ./<Program name> + <input file name>
// Modified form pa1 Lex.c
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
#include "Dictionary.h"

int main(int argc, char *argv[])
{
    int count = 0, i;
    int *lineLength;
    char c = '0';
    char **inputBuffer;
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

    // read in number of lines from input file
    for (c = getc(in); c != EOF; c = getc(in))
        if (c == '\n') // Increment count if this character is newline
            count = count + 1;
    count += 1; // the last line that has EOF

    // printf("The input file has %d words\n", count);
    rewind(in);

    // read in the length for each line
    lineLength = calloc(count, sizeof(int));
    i = 0;
    for (c = getc(in); c != EOF; c = getc(in))
    {
        lineLength[i] += 1;
        if (c == '\n')
        {
            i = i + 1;
        }
    }
    rewind(in);

    Dictionary D = newDictionary(false);

    // allocate backup storage for input file by using the length obtained earlier
    inputBuffer = malloc((count + 1) * sizeof(char *));
    c = 0;
    for (i = 0; i < count + 1; i++)
    {
        if (i < count)
        {
            inputBuffer[i] = calloc(lineLength[i] + 1, sizeof(char));
            // while (c != '\n')
            // {
            //     c = getc(in);
            // }
            fgets(inputBuffer[i], lineLength[i] + 1, in);
            // printf("%s is stored\n", inputBuffer[i]);
        }
        else if (i == count)
            inputBuffer[i] = NULL;
    }

    // insert all words into Dictionary
    for (i = 0; i < count; i++)
    {
        insert(D, inputBuffer[i], i);
    }

    for (i = beginForward(D); currentVal(D) != VAL_UNDEF; i = next(D))
    {
        fprintf(out, "%s", inputBuffer[currentVal(D)]);
    }

    for (i = 0; i <= count; i++)
    {
        if (inputBuffer[i] != NULL)
        {
            free(inputBuffer[i]);
            inputBuffer[i] = NULL;
        }
    }
    free(inputBuffer);
    free(lineLength);
    lineLength = NULL;
    inputBuffer = NULL;
    fclose(in);
    fclose(out);
    freeDictionary(&D);
}
