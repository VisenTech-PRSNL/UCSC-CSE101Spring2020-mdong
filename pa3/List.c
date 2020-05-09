//-----------------------------------------------------------------------------
// List.c
// Implementation file for List ADT
// Programming assignment 3
// Author: MingWei Dong
// CruzID: mdong5
//-----------------------------------------------------------------------------

#include "List.h"

// InitialSize
#define InitialSize 1
#define undefined NULL
// NodeObj
typedef struct NodeObj *Node;
typedef struct NodeObj
{
    int data;
    Node next;
    Node pre;
} NodeObj;

typedef struct ListObj
{
    Node back;
    Node front;
    Node cursor;
    int listLength;
} ListObj;

// Private Types and Functions ------------------------------------------------
// void printList(FILE *out, List Q);
// int countDigits(int data);

// Constructors-Destructors ---------------------------------------------------

// newList()
// Constructor for the List ADT.
// newList create a representation or a container or a empty Queue of a List
// this representation itself does not hold any information other than the address of itself
// the list is not formally built until user insert the first information in it
// therefore everything in this object is yet undefined by calling this function

List newList()
{
    List L = (List)malloc(sizeof(ListObj));
    assert(L != NULL);
    L->listLength = 0;
    L->back = undefined;
    L->front = undefined;
    L->cursor = undefined;
    return L;
}

// freeList()
// Destructor for the List ADT.

void freeList(List *pL)
{
    if (pL != NULL && *pL != NULL)
    {
        if ((*pL)->front != NULL && (*pL)->back != NULL)
        {
            Node current = (*pL)->front;
            Node target;
            while (current != (*pL)->back)
            {
                target = current;
                current = current->next;
                free(target);
            }
            free((*pL)->back);
            free(*pL);
            *pL = NULL;
        }
        else
        {
            free(*pL);
            *pL = NULL;
        }
    }
    // else
    // {
    //     fprintf(stderr, "USAGE: freeList() called on invalid list\n");
    // }
    // if (pL != NULL && *pL != NULL)
    // {
    //     while (index(*pL) != -1)
    //         deleteBack(*pL);
    //     free(*pL);
    //     *pL = NULL;
    // }
}

// Access functions -----------------------------------------------------------
int length(List L)
{
    //puts("Getting length");
    int length = -1;
    if (L != NULL)
        length = L->listLength;
    return length;
} // Returns the number of elements in L.

int index(List L)
{
    int indexNow = -1, i;
    Node helper = NULL;
    if (L->cursor != undefined)
    {
        helper = L->front;
        indexNow = 0;
        for (i = 0; i < L->listLength; i++)
        {
            if (helper != undefined)
            {
                if (helper == L->cursor)
                    break;
                else
                {
                    indexNow += 1;
                    helper = helper->next;
                }
            }
            else
                break;
        }
    }
    return indexNow;
} // Returns index of cursor element if defined, -1 otherwise.

int front(List L)
{
    if (length(L) <= 0)
    {
        fprintf(stderr, "USAGE: front() called on empty list\n");
    }
    int element = -1;
    assert(L != NULL);
    if (length(L) > 0)
        element = L->front->data;
    return element;
} // Returns front element of L. Pre: length()>0

int back(List L)
{
    if (length(L) <= 0)
    {
        fprintf(stderr, "USAGE: back() called on empty list\n");
    }
    int element = -1;
    assert(L != NULL);
    if (length(L) > 0)
        element = L->back->data;
    return element;
} // Returns back element of L. Pre: length()>0

int get(List L)
{
    if (length(L) <= 0)
        fprintf(stderr, "USAGE: back() called on empty list\n");
    else if (index(L) < 0)
        fprintf(stderr, "USAGE: back() called on cursor undefined list\n");

    int element = -1;
    assert(L != NULL);
    if (length(L) > 0 && index(L) >= 0)
        element = L->cursor->data;
    return element;

} // Returns cursor element of L. Pre: length()>0, index()>=0

int equals(List A, List B)
{
    assert(A != NULL && B != NULL);
    int state = false;
    int checked = 0;
    Node checkerA;
    Node checkerB;
    // case:  both list not empty
    if (A->listLength > 0 && B->listLength > 0)
    {
        // first, check list length, front and back element
        if (A->listLength == B->listLength && A->front->data == B->front->data && A->back->data == B->back->data)
        {
            checkerA = A->front;
            checkerB = B->front;
            while (checkerA != NULL && checkerB != NULL)
            {
                // then, check every elements in the list
                if (checkerA->data == checkerB->data)
                {
                    checkerA = checkerA->next;
                    checkerB = checkerB->next;
                    ++checked;
                }
                else
                    break;
            }
            if (checked == length(A))
                state = true;
        }
    }
    // case: both empty, which is for sure equal
    else if (A->listLength == 0 && B->listLength == 0)
        state = true;

    return state;
} // Returns true (1) iff Lists A and B are in same
  // state, and returns false (0) otherwise.

// Manipulation procedures ----------------------------------------------------
void clear(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "clear() called on empty list");
        exit(EXIT_FAILURE);
    }
    if (L != NULL)
    {
        // if the list is properly initialized:
        if (L->front != NULL && L->back != NULL)
        {
            Node current = L->front;
            Node target;
            while (current != L->back)
            {
                target = current;
                current = current->next;
                free(target);
            }
            free(L->back);
            L->cursor = undefined;
            L->front = undefined;
            L->back = undefined;
            L->listLength = 0;
            current = NULL;
            target = NULL;
        }
    }
    // puts("-----LIST RESET-----");
} // Resets L to its original empty state.
void moveFront(List L)
{
    if (L != undefined && L->listLength > 0)
    {
        L->cursor = L->front;
    }
} // If L is non-empty, sets cursor under the front element,
  // otherwise does nothing.
void moveBack(List L)
{
    if (L != undefined && L->listLength > 0)
    {
        L->cursor = L->back;
    }
} // If L is non-empty, sets cursor under the back element,
  // otherwise does nothing.
void movePrev(List L)
{
    if (L != undefined && L->cursor != undefined && L->front != L->cursor)
        L->cursor = L->cursor->pre;
    else if (L != undefined && L->cursor != undefined && L->front == L->cursor)
        L->cursor = undefined;
}

void moveNext(List L)
{
    if (L != undefined && L->cursor != undefined && L->back != L->cursor)
        L->cursor = L->cursor->next;
    else if (L != undefined && L->cursor != undefined && L->back == L->cursor)
        L->cursor = undefined;
}

void prepend(List L, int data)
{
    if (L != undefined)
    {
        Node insertion = malloc(sizeof(NodeObj));
        if (L->front != undefined)
        {
            //puts("normal prepend");
            insertion->data = data; // make a new node
            //printf("new data is %d\n", insertion->data);
            insertion->next = L->front;
            insertion->pre = NULL;
            L->front->pre = insertion; // link in the list
            L->front = insertion;
            L->listLength += 1;
        }
        else
        {
            //puts("prepend on empty list");
            insertion->data = data; // make a new node
            insertion->next = NULL;
            insertion->pre = NULL;
            //puts("node created");
            L->front = insertion;
            L->back = insertion;
            L->listLength += 1;
        }
    }
} // Insert new element into L. If L is non-empty,
  // insertion takes place before front element.
void append(List L, int data)
{
    // puts("APPEND: ");
    if (L != undefined)
    {
        Node insertion = malloc(sizeof(NodeObj));
        if (L->back != undefined)
        {
            // puts("normal append");
            insertion->data = data; // make a new node
            // printf("new data is %d\n", insertion->data);
            insertion->next = NULL;
            insertion->pre = L->back;
            L->back->next = insertion; // link in the list
            L->back = insertion;
            L->listLength += 1;
        }
        else
        {
            // puts("append on empty list");
            insertion->data = data; // make a new node
            insertion->next = NULL;
            insertion->pre = NULL;
            // puts("node created");
            L->front = insertion;
            L->back = insertion;
            L->listLength += 1;
        }
    }
} // Insert new element into L. If L is non-empty,
  // insertion takes place after back element.
void insertBefore(List L, int data)
{
    Node new;
    if (L != NULL && length(L) > 0 && index(L) > 0)
    {
        new = malloc(sizeof(NodeObj));
        new->data = data;
        new->next = L->cursor;
        new->pre = L->cursor->pre;
        L->cursor->pre->next = new; // link the node before the new node
        L->cursor->pre = new;       // link with the cursor node
        L->listLength += 1;
    }
    else if (L != NULL && length(L) > 0 && index(L) == 0)
    {
        prepend(L, data);
    }

} // Insert new element before cursor.
  // Pre: length()>0, index()>=0
void insertAfter(List L, int data)
{
    Node new;
    if (L != NULL && length(L) > 0 && index(L) >= 0 && index(L) < length(L) - 1)
    {
        new = malloc(sizeof(NodeObj));
        new->data = data;
        new->next = L->cursor->next;
        new->pre = L->cursor;
        L->cursor->next->pre = new;
        L->cursor->next = new;
        L->listLength += 1;
    }
    else if (L != NULL && length(L) > 0 && index(L) == length(L) - 1)
    {
        append(L, data);
    }

} // Insert new element after cursor.
  // Pre: length()>0, index()>=0
void deleteFront(List L)
{
    // puts("DELETE FRONT");
    Node target;
    if (L != undefined && L->listLength > 0)
    {
        if (L->cursor == L->front)
            L->cursor = undefined;

        if (L->listLength > 1)
        {
            target = L->front;
            L->front->next->pre = NULL;
            L->front = L->front->next;
            free(target);
            target = NULL;
        }
        else
        {
            // to delete the only element
            target = L->front;
            L->front = NULL;
            L->back = NULL;
            free(target);
            target = NULL;
        }
        L->listLength -= 1;
        // printf("list now have %d elements", L->listLength);
    }

} // Delete the front element. Pre: length()>0
void deleteBack(List L)
{
    // puts("DELETE BACK");
    Node target;
    if (L != undefined && L->listLength > 0)
    {
        if (L->cursor == L->back)
            L->cursor = undefined;

        if (L->listLength > 1)
        {
            target = L->back;
            L->back->pre->next = NULL;
            L->back = L->back->pre;
            free(target);
            target = NULL;
        }
        else
        {
            // to delete the only element
            target = L->back;
            L->front = NULL;
            L->back = NULL;
            free(target);
            target = NULL;
        }
        L->listLength -= 1;
    }
} // Delete the back element. Pre: length()>0
void delete (List L)
{
    if (L->listLength > 0 && index(L) >= 0)
    {
        if (L->cursor == L->front)
            deleteFront(L);
        if (L->cursor == L->back)
            deleteBack(L);
        if (L->cursor != NULL && L->cursor->pre != NULL)
            L->cursor->pre->next = L->cursor->next;
        if (L->cursor != NULL && L->cursor->next != NULL)
            L->cursor->next->pre = L->cursor->pre;
        if (L->cursor != NULL)
        {
            free(L->cursor);
            L->cursor = NULL;
            L->listLength -= 1;
        }
    }
} // Delete cursor element, making cursor undefined.
  // Pre: length()>0, index()>=0

// ADT operations -------------------------------------------------------------

int isEmpty(List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "List Error: isEmpty() called on NULL "
                        "List reference");
        exit(EXIT_FAILURE);
    }

    return (L->front == NULL);
}

void printList(FILE *out, List L)
{
    if (L == NULL)
    {
        fprintf(stderr, "List Error: printList() called on NULL "
                        "List reference");
        exit(EXIT_FAILURE);
    }
    Node tempCursor = L->front;
    while (tempCursor != NULL && tempCursor != L->back)
    {
        fprintf(out, "%d ", tempCursor->data);
        tempCursor = tempCursor->next;
    }
    if (tempCursor != NULL)
        fprintf(out, "%d", tempCursor->data);
}

// Returns a new List representing the same integer
// sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.
List copyList(List L)
{
    // puts("seriously?");
    assert(L != undefined);
    int n;
    Node target = L->front;
    List new = newList();
    assert(new != NULL);
    // printf("%d\n", L->listLength);
    // printf("The new list will has %d elements\n", L->listLength);
    if (target != undefined)
    {
        for (n = 0; n < L->listLength; n++)
        {
            append(new, target->data);
            target = target->next;
        }
    }
    else
    {
        puts("COPY ON EMPTY LIST");
    }

    return new;
}

// Returns a new List which is the concatenation of
// A and B. The cursor in the new List is undefined,
// regardless of the states of the cursors in A and B.
// The states of A and B are unchanged.
List concatList(List A, List B)
{
    List new = undefined;
    return new;
}
