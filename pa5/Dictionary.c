//-----------------------------------------------------------------------------
// Dictionary.c
// Source code for Dictionary ADT
// This file shouldn't be accessed by user
// Modified form CSE 15 pa3
//-----------------------------------------------------------------------------
#include "Dictionary.h"
#include <string.h>
#include <stdbool.h>
#include <assert.h>

enum DictionaryMode
{
	NOT_UNIQUE,
	UNIQUE
};
typedef struct NodeObj *Node;

typedef struct NodeObj
{
	Node parent;
	KEY_TYPE key;
	VAL_TYPE value;
	Node left;
	Node right;
} NodeObj;

typedef struct DictionaryObj
{
	int size;
	char mode;
	Node root;
	Node cursor;
} DictionaryObj;

Node maximum(Node x);
Node minimum(Node x);
Node search(Dictionary D, KEY_TYPE k);
void transplant(Dictionary T, Node u, Node v);
Node successor(Node x);
Node predecessor(Node x);
void printInOrder(FILE *out, Node target);
void clearPostOrder(Dictionary D, Node x);

// newDictionary()
// Constructor for the Dictionary ADT.
Dictionary newDictionary(int unique)
{
	Dictionary D = malloc(sizeof(DictionaryObj));
	assert(D != NULL);
	switch (unique)
	{
	case true:
		D->mode = UNIQUE;
		break;
	case false:
		D->mode = NOT_UNIQUE;
		break;
	}
	D->size = 0;
	D->cursor = NULL;
	D->root = NULL;
	return D;
}

// freeDictionary()
// Destructor for the Dictionary ADT.
void freeDictionary(Dictionary *pD)
{
	makeEmpty(*pD);
	free(*pD);
	*pD = NULL;
}

// ADT operations -------------------------------------------------------------

// size()
// Return the number of (key, value) pairs in Dictionary D.
int size(Dictionary D) //ok
{
	return D->size;
}

int getUnique(Dictionary D)
{
	if (D == NULL)
		return -1;
	return D->mode;
}

// lookup()
VAL_TYPE lookup(Dictionary D, KEY_TYPE k)
{
	if (D == NULL || D->size == 0)
		return VAL_UNDEF;
	Node cursor = D->root;
	while (cursor != NULL && KEY_CMP(cursor->key, k) != 0)
	{
		if (KEY_CMP(cursor->key, k) > 0) // if c.key larger than k
			cursor = cursor->left;		 // move cursor to a smaller node
		else							 // otherwise
			cursor = cursor->right;		 // move to a larger node
	}
	if (cursor == NULL)
		return VAL_UNDEF;
	return cursor->value;
}

// insert()
void insert(Dictionary D, KEY_TYPE k, VAL_TYPE v)
{
	if (D == NULL)
		return;
	if (getUnique(D) == true)
	{
		if (lookup(D, k) != VAL_UNDEF)
			return;
	}
	Node z = malloc(sizeof(NodeObj));
	z->key = calloc(strlen(k) + 1, sizeof(char));
	Node y = NULL;
	Node x = D->root;
	z->value = v;
	strcpy(z->key, k);
	z->left = NULL;
	z->right = NULL;

	while (x != NULL)
	{
		y = x;
		if (KEY_CMP(z->key, x->key) < 0)
			x = x->left;
		else
			x = x->right;
	}
	z->parent = y;
	if (y == NULL)
		D->root = z; // tree T was empty
	else if (KEY_CMP(z->key, y->key) < 0)
		y->left = z;
	else
		y->right = z;
	D->size += 1;
}

// delete()
void delete (Dictionary D, char *k)
{
	Node z = search(D, k);
	if (z == NULL)
		return;

	if (z->left == NULL)
		transplant(D, z, z->right);
	else if (z->right == NULL)
		transplant(D, z, z->left);
	else
	{
		Node y = minimum(z->right);
		if (y->parent != z)
		{
			transplant(D, y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		transplant(D, z, y);
		y->left = z->left;
		y->left->parent = y;
	}
	D->size -= 1;
	if (D->cursor == z)
		D->cursor = NULL;
	free(z->key);
	free(z);
}

// makeEmpty()
// Reset D to the empty state, the empty set of pairs.
void makeEmpty(Dictionary D)
{
	if (D != NULL && D->root != NULL)
	{
		clearPostOrder(D, D->root);
		D->root = NULL;
		D->size = 0;
		D->cursor = NULL;
	}
}

void clearPostOrder(Dictionary D, Node x)
{
	if (x != NULL)
	{
		clearPostOrder(D, x->left);
		clearPostOrder(D, x->right);
		free(x->key);
		free(x);
	}
}

VAL_TYPE beginForward(Dictionary D)
{
	if (D == NULL)
		return VAL_UNDEF;
	Node min = minimum(D->root);
	D->cursor = min;
	if (min == NULL)
		return VAL_UNDEF;
	return min->value;
}
VAL_TYPE beginReverse(Dictionary D)
{
	if (D == NULL)
		return VAL_UNDEF;
	Node max = maximum(D->root);
	D->cursor = max;
	if (max == NULL)
		return VAL_UNDEF;
	return max->value;
}
KEY_TYPE currentKey(Dictionary D)
{
	if (D == NULL || D->cursor == NULL)
		return KEY_UNDEF;
	return D->cursor->key;
}
VAL_TYPE currentVal(Dictionary D)
{
	if (D == NULL || D->cursor == NULL)
		return VAL_UNDEF;
	return D->cursor->value;
}
Node successor(Node x)
{
	if (x == NULL)
		return NULL;
	Node y;
	if (x->right != NULL)
		return minimum(x->right);
	y = x->parent;
	while (y != NULL && x == y->right)
	{
		x = y;
		y = y->parent;
	}
	return y;
}

Node predecessor(Node x)
{
	if (x == NULL)
		return NULL;
	Node y;
	if (x->left != NULL)
		return maximum(x->left);
	y = x->parent;
	while (y != NULL && x == y->left)
	{
		x = y;
		y = y->parent;
	}
	return y;
}

VAL_TYPE next(Dictionary D)
{
	if (D == NULL || D->cursor == NULL)
		return VAL_UNDEF;
	D->cursor = successor(D->cursor);
	if (D->cursor == NULL)
		return VAL_UNDEF;
	return D->cursor->value;
}

VAL_TYPE prev(Dictionary D)
{
	if (D == NULL || D->cursor == NULL)
		return VAL_UNDEF;
	D->cursor = predecessor(D->cursor);
	if (D->cursor == NULL)
		return VAL_UNDEF;
	return D->cursor->value;
}

// Other Operations -----------------------------------------------------------

Node minimum(Node x)
{
	if (x == NULL)
		return NULL;
	while (x->left != NULL)
		x = x->left;
	return x;
}
Node maximum(Node x)
{
	if (x == NULL)
		return NULL;
	while (x->right != NULL)
		x = x->right;
	return x;
}

Node search(Dictionary D, KEY_TYPE k)
{
	if (D == NULL || D->size == 0)
		return NULL;
	Node extCursor = D->root;
	while (extCursor != NULL && KEY_CMP(extCursor->key, k) != 0)
	{
		if (KEY_CMP(extCursor->key, k) > 0) // if c.key larger than k
			extCursor = extCursor->left;	// move cursor to a smaller node
		else								// otherwise
			extCursor = extCursor->right;	// move to a larger node
	}
	return extCursor;
}

/*   In order to move subtrees around within the binary search tree, we deﬁne a 
 * subroutine TRANSPLANT, which replaces one subtree as a child of its parent with 
 * another subtree. When TRANSPLANT replaces the subtree rooted at node u with 
 * the subtree rooted at node v, node u’s parent becomes node v’s parent, and u’s
 * parent ends up having v as its appropriate child.
 */
void transplant(Dictionary T, Node u, Node v)
{
	if (u->parent == NULL)
		T->root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;
	if (v != NULL)
		v->parent = u->parent;
}

void printDictionary(FILE *out, Dictionary D)
{
	// if (D != NULL && D->root == NULL)
	// fprintf(out, "printDictionary(): called on declared but uninitalized Dictionary\n");
	if (D != NULL && D->root != NULL)
		printInOrder(out, D->root);
}

void printInOrder(FILE *out, Node target)
{
	if (target != NULL)
	{
		printInOrder(out, target->left);
		fprintf(out, "" KEY_FORMAT " " VAL_FORMAT "\n",
				target->key, target->value);
		printInOrder(out, target->right);
	}
}