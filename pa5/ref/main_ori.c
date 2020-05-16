#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define KEY_TYPE char*
#define VAL_TYPE int
#define KEY_UNDEF NULL
#define VAL_UNDEF -1
#define KEY_FORMAT "%s"
#define VAL_FORMAT "%d"
#define KEY_CMP(x,y) strcmp((x),(y))
struct Node;
typedef struct DictionaryObj* Dictionary;

typedef struct Node
{
	KEY_TYPE key;
	VAL_TYPE value;
	Node* p;
	Node* left;
	Node* right;
}Node;

typedef struct DictionaryObj
{
	int unique;
	int num;
	Node* current;
	Node* root;
} DictionaryObj;

Dictionary newDictionary(int unique);
int size(Dictionary D);
int getUnique(Dictionary D);
void insert(Dictionary D, KEY_TYPE k, VAL_TYPE v);
Node* newNode(KEY_TYPE k, VAL_TYPE v);
void transplant(Dictionary T,Node* u,Node* v);	//用另一棵子树替换一棵子树并成为其双亲的孩子结点
Node* search(Node* x, KEY_TYPE k);
Node* searchDictionary(Dictionary D, KEY_TYPE k);
Node* minimum(Node* x);
Node* maximum(Node* x);
Node* minimumDictionary(Dictionary D);
Node* maximumDictionary(Dictionary D);
void delete(Dictionary D, KEY_TYPE k);
void showNode(FILE* out, Node* pN);
void printBT(FILE* out, Node* pN);
void printDictionary(FILE* out, Dictionary D);
VAL_TYPE lookup(Dictionary D, KEY_TYPE k);
void makeEmpty(Dictionary D);
void empty(Node* pN);
void freeDictionary(Dictionary* pD);
VAL_TYPE beginForward(Dictionary D);
VAL_TYPE beginReverse(Dictionary D);
KEY_TYPE currentKey(Dictionary D);
VAL_TYPE currentVal(Dictionary D);
Node* successor(Node* x);
Node* predecessor(Node* x);
VAL_TYPE next(Dictionary D);
VAL_TYPE prev(Dictionary D);







int main()
{
	int i, n=26;
   Dictionary A = newDictionary(0);
   Dictionary B = newDictionary(1);
   char* word[] = { "n","z","w","k","i","c","l","d","t","a", 
                    "e","y","b","h","v","f","s","m","x","r",
                    "o","u","p","g","j","q" };
   VAL_TYPE x;
   VAL_TYPE y;

   // add pairs to A --------------------------------------
   for(i=0; i<n; i++){
      insert(A, word[i], i);
   }

   // add pairs to B
   for(i=n-1; i>=0; i--){
      insert(B, word[i], i);
   }


   // forward iteration over A ----------------------------
   printf("forward A:\n");
   for(x=beginForward(A); currentVal(A)!=VAL_UNDEF; x=next(A)){
      printf("key: "KEY_FORMAT" value: "VAL_FORMAT"\n", currentKey(A), x);
   }
   printf("\n\n");

   // reverse iteratation over B 
   printf("reverse B:\n");
   for(y=beginReverse(B); currentVal(B)!=VAL_UNDEF; y=prev(B)){
      printf("key: "KEY_FORMAT" value: "VAL_FORMAT"\n", currentKey(B), y);
   }
   printf("\n\n");


   // print Dictionary A ----------------------------------
   printf("Dictionary A (%sunique keys):\n", (getUnique(A)?"":"non-"));
   printDictionary(stdout, A);
   printf("\n");

   // print Dictionary B
   printf("Dictionary B (%sunique keys):\n", (getUnique(B)?"":"non-"));
   printDictionary(stdout, B);
   printf("\n");


   // delete keys from A ----------------------------------
   for(i=0; i<n; i+=2){
      delete(A, word[i]);
   }

   // print Dictionary A after deletions
   printf("Dictionary A (%sunique keys):\n", (getUnique(A)?"":"non-"));
   printf("after deletions:\n");
   printDictionary(stdout, A);
   printf("\n");


   // delete keys from B ----------------------------------
   for(i=1; i<n; i+=2){
      delete(B, word[i]);
   }

   // print Dictionary B after deletions
   printf("Dictionary B (%sunique keys):\n", (getUnique(B)?"":"non-"));
   printf("after deletions:\n");
   printDictionary(stdout, B);
   printf("\n");


   // insert duplicates into A ----------------------------
   for(i=1; i<n; i+=2){
      insert(A, word[i], i);
   }

   // print Dictionary A after insertions
   printf("Dictionary A (%sunique keys):\n", (getUnique(A)?"":"non-"));
   printf("after insertions:\n");
   printDictionary(stdout, A);
   printf("\n");

   // uncomment line below to get error message
   // insert(B, word[10], 10);
   // Dictionary Error: 
   // calling insert() on existing key: e


   // free heap memory ------------------------------------
   freeDictionary(&A);
   freeDictionary(&B);
   return 0;
	
}

Dictionary newDictionary(int unique)
{
	Dictionary B = (Dictionary)malloc(sizeof(DictionaryObj));
	B->unique = unique;
	B->num = 0;
	B->current = NULL;
	B->root = NULL;
}

int size(Dictionary D)
{
	return D->num;
}

int getUnique(Dictionary D)
{
	if(D->unique == 0)
		return 0;
	return 1;
}
void showNode(FILE* out, Node* pN)
{
	if(pN != NULL)
		fprintf(stdout, "key:"KEY_FORMAT"  value:"VAL_FORMAT"  Me:%x  P:%x  L:%x  R:%x\n",pN->key,pN->value,pN,pN->p,pN->left,pN->right);
}
Node* newNode(KEY_TYPE k, VAL_TYPE v)
{
	Node* z = (Node*)malloc(sizeof(Node));
	z->key = k;
	z->value = v;
	z->p = NULL;
	z->left = NULL;
	z->right = NULL; 
	return z;
}
void insert(Dictionary D, KEY_TYPE k, VAL_TYPE v)
{
	if(D == NULL)
		return;
	if(getUnique(D)==1)
	{
		Node* s = search(D->root,k);
		if(s!=NULL)
			return;
	}
	
	
	Node* z = newNode(k,v);
	
	Node* y = NULL;
	Node* x = D->root;
	while(x != NULL)
	{
		y = x;
		if(KEY_CMP(x->key,z->key) > 0)
			x = x->left;
		else
			x = x->right;
	}
	z->p = y;
	if(y==NULL)
		D->root = z;
	else if(KEY_CMP(z->key,y->key) < 0)
		y->left = z;
	else
		y->right = z;
	D->num++;
}
void transplant(Dictionary T,Node* u,Node* v)
{
	if(u->p == NULL)
		T->root = v;
	else if(u == u->p->left)
		u->p->left = v;
	else
		u->p->right = v;
	if(v!=NULL)
		v->p = u->p;
}

Node* search(Node* x, KEY_TYPE k)
{
	if(x==NULL || KEY_CMP(x->key,k)==0 )
		return x;
	else if(KEY_CMP(x->key,k)>0)
		return search(x->left, k);
	else
		return search(x->right, k);
}
Node* searchDictionary(Dictionary D, KEY_TYPE k)
{
	if(D==NULL)
		return NULL;
	return search(D->root, k);
}
Node* minimum(Node* x)
{
	if(x==NULL)
		return NULL;
	while(x->left != NULL)
		x = x->left;
	return x;
}
Node* maximum(Node* x)
{
	if(x==NULL)
		return NULL;
	while(x->right != NULL)
		x = x->right;
	return x;
}
Node* minimumDictionary(Dictionary D)
{
	return minimum(D->root);
}
Node* maximumDictionary(Dictionary D)
{
	return maximum(D->root);
}
void delete(Dictionary D, KEY_TYPE k)
{
	Node* z = searchDictionary(D, k);
	if(z==NULL)
		return;
	
	if(z->left == NULL)
		transplant(D, z, z->right);
	else if(z->right == NULL)
		transplant(D, z, z->left);
	else
	{
		Node* y = minimum(z->right);
		if(y->p != z)
		{
			transplant(D, y, y->right);
			y->right = z->right;
			y->right->p = y;
		}
		transplant(D, z, y);
		y->left = z->left;
		y->left->p = y;
	}
	D->num--;
	free(z);
}
void printDictionary(FILE* out, Dictionary D)
{
	if(D!=NULL)
	{
		printBT(out, D->root);
	}
}
void printBT(FILE* out, Node* pN)
{
	if(pN != NULL)
	{
		printBT(out, pN->left);
		fprintf(out, ""KEY_FORMAT" "VAL_FORMAT"\n", pN->key, pN->value);
//		showNode(out, pN);
		printBT(out, pN->right);
	}
}
VAL_TYPE lookup(Dictionary D, KEY_TYPE k)
{
	if(D==NULL)
		return VAL_UNDEF;
	Node* pN = search(D->root, k);
	if(pN == NULL)
		return VAL_UNDEF;
	return pN->value;
}
void empty(Node* pN)
{
	if(pN != NULL)
	{
		empty(pN->left);
		empty(pN->right);
		free(pN);
	}
}
void makeEmpty(Dictionary D)
{
	empty(D->root);
	D->num = 0;
	D->current = NULL;
	D->root = NULL;
}
void freeDictionary(Dictionary* pD)
{
	makeEmpty(*pD);
	free(*pD);
	*pD = NULL;
}
VAL_TYPE beginForward(Dictionary D)
{
	if(D==NULL)
		return VAL_UNDEF;
	Node* min = minimumDictionary(D);
	D->current = min;
	if(min == NULL)
		return VAL_UNDEF;
	return min->value;
}
VAL_TYPE beginReverse(Dictionary D)
{
	if(D==NULL)
		return VAL_UNDEF;
	Node* max = maximumDictionary(D);
	D->current = max;
	if(max == NULL)
		return VAL_UNDEF;
	return max->value;
}
KEY_TYPE currentKey(Dictionary D)
{
	if(D==NULL || D->current==NULL)
		return KEY_UNDEF;
	return D->current->key;
}
VAL_TYPE currentVal(Dictionary D)
{
	if(D==NULL || D->current==NULL)
		return VAL_UNDEF;
	return D->current->value;
}
Node* successor(Node* x)
{
	if(x==NULL)
		return NULL;
	Node* y;
	if(x->right != NULL)
		return minimum(x->right);
	y = x->p;
	while(y!=NULL && x==y->right)
	{
		x = y;
		y = y->p;
	}
	return y;
}

Node* predecessor(Node* x)
{
	if(x==NULL)
		return NULL;
	Node* y;
	if(x->left != NULL)
		return maximum(x->left);
	y = x->p;
	while(y!=NULL && x==y->left)
	{
		x = y;
		y = y->p;
	}
	return y;
}

VAL_TYPE next(Dictionary D)
{
	if(D==NULL || D->current==NULL)
		return VAL_UNDEF;
	D->current = successor(D->current);
	if(D->current==NULL)
		return VAL_UNDEF;
	return D->current->value;
}

VAL_TYPE prev(Dictionary D)
{
	if(D==NULL || D->current==NULL)
		return VAL_UNDEF;
	D->current = predecessor(D->current);
	if(D->current==NULL)
		return VAL_UNDEF;
	return D->current->value;
}


















