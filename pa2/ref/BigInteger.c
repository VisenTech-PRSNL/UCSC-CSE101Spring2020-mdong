#include "BigInteger.h"

#define POWER 1
#define BASE 10


typedef struct BigIntegerObj // BigInteger reference type
{
	int sign;
	List bigInt;
} BigIntegerObj;

BigInteger newBigInteger() // newBigInteger()
{
	BigInteger N = (BigInteger)malloc(sizeof(BigIntegerObj));
	N->sign = 0;
	N->bigInt = newList();
	append(N->bigInt, 0);
	return N;
}

void freeBigInteger(BigInteger *pN) // freeBigInteger()
{
	if (pN != NULL && *pN != NULL)
	{
		(*pN)->bigInt;
		if ((*pN)->bigInt != NULL)
			freeList(&((*pN)->bigInt));
		free(*pN);
		*pN = NULL;
	}
	else
	{
		fprintf(stderr, "USAGE: freeBigInteger() called on invalid BigInteger\n");
	}
}

int sign(BigInteger N) // sign()
{
	if (N != NULL)
		return N->sign;
}

int compare(BigInteger A, BigInteger B) // compare()
{
	BigInteger N = diff(A, B);
	return N->sign;
}

int equals(BigInteger A, BigInteger B) // equals()
{
	if (A->sign != B->sign)
		return 0;
	return equals(A->bigInt, B->bigInt);
}

void makeZero(BigInteger N) // makeZero()
{
	N->sign = 0;
	N->bigInt = newList();
	append(N->bigInt, 0);
}

void negate(BigInteger N) // negate()
{
	N->sign = -N->sign;
}

BigInteger stringToBigInteger(char *s) // stringToBigInteger()
{
	BigInteger N = newBigInteger();
	if (s[0] == '+')
		N->sign = 1;
	else if (s[0] == '-')
		N->sign = -1;

	if (strlen(s) > 1)
		N->bigInt = strToList(s + 1);
	else
		N->bigInt = strToList(s);

	moveFront(N->bigInt);
	if (length(N->bigInt) == 1 && get(N->bigInt) == 0)
		N->sign = 0;
	return N;
}

BigInteger copy(BigInteger N) // copy()
{
	BigInteger copyN = newBigInteger();
	copyN->sign = N->sign;
	copyN->bigInt = copyList(N->bigInt);
	return copyN;
}

void add(BigInteger S, BigInteger A, BigInteger B) // add()
{
	BigInteger result = sum(A, B);
	overWritingBigInteger(S, result);
}

BigInteger sum(BigInteger A, BigInteger B) // sum()
{
	BigInteger N = (BigInteger)malloc(sizeof(BigIntegerObj));
	if (A->sign == B->sign)
	{ //同号相加
		N->sign = A->sign;
		N->bigInt = jia(A->bigInt, B->bigInt);
	}
	else //异号相减
	{
		int x = compareList(A->bigInt, B->bigInt);
		if (x == 0)
		{
			N->sign = 0;
			N->bigInt = newList();
			append(N->bigInt, 0);
		}
		else if (x == 1)
		{
			N->sign = A->sign;
			N->bigInt = intersection(A->bigInt, B->bigInt);
		}
		else
		{
			N->sign = B->sign;
			N->bigInt = intersection(B->bigInt, A->bigInt);
		}
	}
	return N;
}

void subtract(BigInteger S, BigInteger A, BigInteger B) // subtract()
{
	BigInteger result = diff(A, B);
	overWritingBigInteger(S, result);
}

BigInteger diff(BigInteger A, BigInteger B) // diff()
{
	BigInteger copyA = copy(A);
	BigInteger copyB = copy(B);
	negate(copyB);
	return sum(copyA, copyB);
}

void multiply(BigInteger S, BigInteger A, BigInteger B) // multiply()
{
	BigInteger result = prod(A, B);
	overWritingBigInteger(S, result);
}

BigInteger prod(BigInteger A, BigInteger B) // prod()
{
	BigInteger N = (BigInteger)malloc(sizeof(BigIntegerObj));
	BigInteger copyA = copy(A);
	BigInteger copyB = copy(B);
	if (copyA->sign == 0 && copyB->sign == 0)
		N->sign = 0;
	else if (copyA->sign == copyB->sign)
		N->sign = 1;
	else
		N->sign = -1;

	N->bigInt = times(copyA->bigInt, copyB->bigInt);

	moveFront(N->bigInt);
	if (length(N->bigInt) == 1 && get(N->bigInt) == 0)
		N->sign = 0;
	return N;
}

void printBigInteger(FILE *out, BigInteger N) // printBigInteger()
{
	if (N == NULL)
	{
		fprintf(stderr, "BigInteger Error: printBigInteger() called on NULL "
						"BigInteger reference");
		exit(EXIT_FAILURE);
	}
	int sign = N->sign;
	if (sign == -1)
		fprintf(out, "-");
	List L = N->bigInt;
	moveFront(L);
	int i = 0;
	for (moveFront(L); index(L) >= 0; moveNext(L))
	{
		if (i == 0)
			fprintf(out, "%d ", get(L));
		else
			fprintf(out, "%0*d ", POWER, get(L));
		i++;
	}
}

//=========================================================================================

long strToInt(char *s)
{ //字符串转整数，逆序
	long sum = 0;
	int i = strlen(s) - 1;
	for (; i >= 0; i--)
		sum = sum * 10 + (s[i] - '0');
	return sum;
}
long getInt(char *s)
{ //提取字符串前POWER位，转整数（逆序）
	int i = 0;
	char ss[POWER + 1];
	for (i = 0; i < POWER; i++)
		ss[i] = '0';
	ss[POWER] = '\0';
	for (i = 0; i < strlen(s); i++)
	{
		if (i >= POWER)
			break;
		ss[i] = s[i];
	}
	return strToInt(ss);
}

List strToList(char *s)
{ //字符串转List
	int i = 0;
	int L = strlen(s);
	char ss[L + 1];
	for (i = 0; i < L; i++)
		ss[L - 1 - i] = s[i];
	ss[L] = '\0';
	List A = newList();
	for (i = 0; i < L; i += POWER)
	{
		long x = getInt(ss + i);
		prepend(A, x);
	}
	moveFront(A);
	return A;
}

List listTrim(List A)
{ //删除多余的0
	moveFront(A);
	while (index(A) >= 0 && get(A) == 0)
	{
		deleteFront(A);
		moveFront(A);
	}
	if (index(A) == -1)
		append(A, 0);
	return A;
}

List jia(List A, List B)
{
	List L = newList();
	ElemType mod = 0;
	for (moveBack(A), moveBack(B); index(A) >= 0 || index(B) >= 0; movePrev(A), movePrev(B))
	{
		ElemType a = 0, b = 0;
		if (index(A) >= 0)
			a = get(A);
		if (index(B) >= 0)
			b = get(B);
		ElemType sum = a + b + mod;
		// printf("%d+%d+%d=%d\n",a,b,mod,sum%BASE);
		prepend(L, sum % BASE);
		mod = sum / BASE;
	}
	if (mod != 0)
		prepend(L, mod);
	return listTrim(L);
}

List intersection(List A, List B)
{ //大整数减小整数
	List L = newList();
	ElemType mod = 0;
	for (moveBack(A), moveBack(B); index(A) >= 0 || index(B) >= 0; movePrev(A), movePrev(B))
	{
		ElemType a = 0, b = 0;
		if (index(A) >= 0)
			a = get(A);
		if (index(B) >= 0)
			b = get(B);
		ElemType sum = a - b + mod;
		if (sum < 0)
		{
			sum += BASE;
			mod = -1;
		}
		else
			mod = 0;
		prepend(L, sum);
	}
	if (mod != 0)
		prepend(L, mod);
	return listTrim(L);
}

List chen(List A, ElemType x)
{
	List L = newList();
	ElemType mod = 0;
	for (moveBack(A); index(A) >= 0; movePrev(A))
	{
		ElemType a = 0, sum = 0;
		if (index(A) >= 0)
			a = get(A);
		sum = a * x + mod;
		prepend(L, sum % BASE);
		mod = sum / BASE;
	}
	if (mod != 0)
		prepend(L, mod);
	return L;
}

List times(List A, List B)
{
	List sum = newList();
	int i = 0, j = 0;
	for (moveBack(B); index(B) >= 0; movePrev(B))
	{
		List L = chen(A, get(B));
		for (j = 0; j < i; j++)
			append(L, 0);
		sum = jia(sum, L);
		i++;
	}
	return listTrim(sum);
}

int compareList(List A, List B)
{
	if (length(A) > length(B))
		return 1;
	if (length(A) < length(B))
		return -1;
	for (moveFront(A), moveFront(B); index(A) >= 0 && index(B) >= 0; moveNext(A), moveNext(B))
	{
		if (get(A) > get(B))
			return 1;
		if (get(A) < get(B))
			return -1;
	}
	return 0;
}

void overWritingBigInteger(BigInteger goal, BigInteger X)
{
	goal->sign = X->sign;
	goal->bigInt = X->bigInt;
}
