//-----------------------------------------------------------------------------
// DictionaryTest.c
// Private Test client for Dictionary ADT
//-----------------------------------------------------------------------------
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "Dictionary.h"

int main()
{
    Dictionary A = newDictionary(true);
    Dictionary B = newDictionary(false);
    int i;
    char *wordList[] = {
        "decide", "toothpaste", "lowly", "robin", "reign", "crowd",
        "pies", "reduce", "tendency", "surround", "finger", "rake",
        "alleged", "hug", "nest", "punishment", "eggnog", "side",
        "beef", "exuberant", "sort", "scream", "zip", "hair",
        "ragged", "damage", "thought", "jump", "frequent", "substance",
        "head", "step", "faithful", "sidewalk", "pig", "raspy",
        "juggle", "shut", "maddening", "rock", "telephone", "selective"};

    // NonEmpty_makeEmpty Test
    insert(A, "c", 3);
    insert(A, "b", 2);
    insert(A, "a", 1);
    beginForward(A);
    makeEmpty(A);
    if (currentKey(A) != KEY_UNDEF || currentVal(A) != VAL_UNDEF || size(A) != 0)
        printf("Test NonEmpty_makeEmpty: FAILED: test 1\n");

    // Delete_value Test
    insert(A, "d", 1);
    insert(A, "b", 5);
    insert(A, "a", 10);
    insert(A, "c", 15);
    insert(A, "f", 20);
    insert(A, "e", 25);
    insert(A, "g", 30);
    beginForward(A);
    delete (A, "a");
    if (currentKey(A) != KEY_UNDEF || currentVal(A) != VAL_UNDEF)
        printf("Test Delete_value: FAILED: test 1\n");
    beginReverse(A);
    delete (A, "d");
    if (strcmp(currentKey(A), "g") != 0 || currentVal(A) != 30)
        printf("Test Delete_value: FAILED: test 2\n");
    makeEmpty(A);

    // NonUnique_beginForward Test
    insert(B, "d", 2);
    insert(B, "d", 5);
    insert(B, "d", 1);
    if (beginForward(B) != 2)
        printf("Test NonUnique_beginForward: FAILED: test 1\n");
    next(B);
    if (currentVal(B) != 5)
        printf("Test NonUnique_beginForward: FAILED: test 2\n");

    for (i = 0; i < 42; i++)
        insert(A, wordList[i], i);
    printDictionary(stdout, A);
    printf("forward A:\n");
    for (i = beginForward(A); currentVal(A) != VAL_UNDEF; i = next(A))
    {
        printf("key: " KEY_FORMAT " value: " VAL_FORMAT "\n", currentKey(A), i);
    }
    printf("\n\n");
    makeEmpty(A);
    printDictionary(stdout, A);
    freeDictionary(&A);
    freeDictionary(&B);
}