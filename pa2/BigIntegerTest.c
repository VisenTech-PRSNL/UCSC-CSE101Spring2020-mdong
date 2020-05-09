/**********************************************
 * 
 *  BigIntegerTest.c
 *  several hard-coded test for BigInteger.c
 *  Author_ID: mdong5
 * 
**********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <signal.h>
#include <setjmp.h>
#include "List.h"
#include "BigInteger.h"

int main()
{
	puts("----------TEST START----------");
	BigInteger N = newBigInteger();
	printBigInteger(stdout, N);
	printf("\n");

	// printf("%d, %ld\n", atoi("0000"), strlen("0000"));
	// printf("STRING TO LONG: %ld\n", privateStringToLong("00012345"));
	char sInt1[] = "9876543";
	char sInt2[] = "-123456789";
	char sInt3[] = "+861352277135783129503261861155135713910021326";
	char sInt4[] = "+12345";
	char sInt5[] = "+12345";
	char sInt6[] = "12300";
	char sInt7[] = "12345";
	BigInteger N1 = stringToBigInteger(sInt1);
	BigInteger N2 = stringToBigInteger(sInt2);
	BigInteger N3 = stringToBigInteger(sInt3);
	BigInteger N4 = stringToBigInteger(sInt4);
	BigInteger N5 = stringToBigInteger(sInt5);
	BigInteger N6 = stringToBigInteger(sInt6);
	BigInteger N7 = stringToBigInteger(sInt7);

	puts("----- ONE -----");
	printBigInteger(stdout, N1);
	printf("\n");
	printBigInteger(stdout, N2);
	printf("\n");
	printBigInteger(stdout, N3);
	printf("\n");
	printBigInteger(stdout, N4);
	printf("\n");
	printBigInteger(stdout, N5);
	printf("\n");

	puts("----- TWO -----");
	printf("%d %d %d %d\n", sign(N1), sign(N2), sign(N3), sign(N));

	printf("%d %d %d %d\n", compare(N1, N2), compare(N2, N1), compare(N1, N1), compare(N1, N3));

	printf("%d %d \n", equals(N1, N2), equals(N1, N1));

	BigInteger copyN1 = copy(N1);
	printBigInteger(stdout, copyN1);
	printf("\n");

	// 	BigInteger sumResult = sum(N1,N2);
	// 	BigInteger diffResult = diff(N1,N2);
	// 	BigInteger prodResult = prod(N1,N2);
	// 	printBigInteger(stdout, sumResult);
	// 	printf("\n");
	// 	printBigInteger(stdout, diffResult);
	// 	printf("\n");
	// 	printBigInteger(stdout, prodResult);
	// 	printf("\n");
	puts("----- THREE -----");
	add(N, N4, N5);
	printBigInteger(stdout, N);
	printf("\n");
	makeZero(N5);
	printBigInteger(stdout, N5);
	printf("\n");

	puts("----- FOUR -----");
	freeBigInteger(&N5);
	N5 = stringToBigInteger("-12345");
	add(N, N4, N5);
	printBigInteger(stdout, N);
	printf("\n");

	puts("----- FIVE -----");
	add(N, N1, N2);
	printBigInteger(stdout, N);
	printf("\n");
	makeZero(N);
	add(N, N2, N2);
	printBigInteger(stdout, N);
	printf("\n");
	makeZero(N4);
	makeZero(N5);
	add(N, N4, N5);
	printBigInteger(stdout, N);
	printf("\n");

	puts("----- SIX -----");
	subtract(N, N1, N2);
	printBigInteger(stdout, N);
	printf("\n");
	makeZero(N4);
	makeZero(N5);
	subtract(N, N4, N5);
	printBigInteger(stdout, N);
	printf("\n");
	freeBigInteger(&N4);
	freeBigInteger(&N5);
	N4 = stringToBigInteger(sInt4);
	N5 = stringToBigInteger(sInt5);
	subtract(N, N4, N5);
	printBigInteger(stdout, N);
	printf("\n");
	printf("sign N6 : %d\n", sign(N6));
	subtract(N, N4, N6);
	printBigInteger(stdout, N);
	printf("\n");

	puts("----- SEVEN -----");
	// printf("count down cleared?: %s\n", countDown(absolute(N7)) == true ? "true" : "false");
	multiply(N, N1, N2);
	printf("N1 * N2 = ");
	printBigInteger(stdout, N);
	printf("\n");

	
	freeBigInteger(&N);
	freeBigInteger(&N1);
	freeBigInteger(&N2);
	freeBigInteger(&N3);
	freeBigInteger(&N4);
	freeBigInteger(&N5);
	freeBigInteger(&N6);
	freeBigInteger(&N7);
	freeBigInteger(&copyN1);
	N = NULL;
	N1 = NULL;
	N2 = NULL;
	puts("----------TEST END----------");

	return 0;
}