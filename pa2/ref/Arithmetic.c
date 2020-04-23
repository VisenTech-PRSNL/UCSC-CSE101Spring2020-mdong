#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <signal.h>
#include <setjmp.h>
#include "List.h"
#include "BigInteger.h"


void AsB(FILE* out, BigInteger A, BigInteger B)
{	//A+B
	BigInteger sumResult = sum(A,B);
	printBigInteger(out,sumResult);
    printf("\n");
}

void A_B(FILE* out, BigInteger A, BigInteger B)
{	//A-B
	BigInteger diffResult = diff(A,B);
	printBigInteger(out,diffResult);
    printf("\n");
}

void A_A(FILE* out, BigInteger A, BigInteger B)
{	//A-A
	BigInteger diffResult = diff(A,A);
	printBigInteger(out,diffResult);
    printf("\n");
}

void A3_B2(FILE* out, BigInteger A, BigInteger B)
{	//3A-2B
	BigInteger A3 = prod(stringToBigInteger("+3"),A);
	BigInteger B2 = prod(stringToBigInteger("+2"),B);
	BigInteger result = diff(A3,B2);
	printBigInteger(out,result);
    printf("\n");
}

void AB(FILE* out, BigInteger A, BigInteger B)
{	//AB
	BigInteger prodResult = prod(A,B);
	printBigInteger(out,prodResult);
    printf("\n");
}

void AA(FILE* out, BigInteger A, BigInteger B)
{	//A*A
	BigInteger prodResult = prod(A,A);
	printBigInteger(out,prodResult);
    printf("\n");
}

void BB(FILE* out, BigInteger A, BigInteger B)
{	//B*B
	BigInteger prodResult = prod(B,B);
	printBigInteger(out,prodResult);
    printf("\n");
}

void A94xB165(FILE* out, BigInteger A, BigInteger B)
{	//9*A^4+16*B^5
	BigInteger AA = prod(A,A);
	BigInteger AAAA = prod(AA,AA);
	BigInteger A9_4 = prod(AAAA,stringToBigInteger("+3"));
	
	BigInteger BB = prod(B,B);
	BigInteger BBBB = prod(BB,BB);
	BigInteger BBBBB = prod(BBBB,B);
	BigInteger B16_5 = prod(BBBBB,stringToBigInteger("+16"));
	BigInteger sumResult = sum(A9_4,B16_5);
	printBigInteger(out,sumResult);
    printf("\n");
}

//=======================================

int main()
{
	
	char sInt1[] = "+999999";
	char sInt2[] = "-123456789";
	BigInteger A = stringToBigInteger(sInt1);
	BigInteger B = stringToBigInteger(sInt2);
	
	printBigInteger(stdout,A);
    printf("\n");
    printBigInteger(stdout,B);
    printf("\n");
    
    AsB(stdout, A, B);
    A_B(stdout, A, B);
    A_A(stdout, A, B);
    A3_B2(stdout, A, B);
    AB(stdout, A, B);
    AA(stdout, A, B);
    BB(stdout, A, B);
	A94xB165(stdout, A, B);
	return 0;
	
}
