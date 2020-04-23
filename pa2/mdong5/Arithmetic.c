/**********************************************
 * 
 *  Arithmetic.c
 *  A client that take use of BigInteger operators
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

void AsB(FILE *out, BigInteger A, BigInteger B)
{ //A+B
	BigInteger sumResult = sum(A, B);
	printBigInteger(out, sumResult);
	printf("\n");
}

void A_B(FILE *out, BigInteger A, BigInteger B)
{ //A-B
	BigInteger diffResult = diff(A, B);
	printBigInteger(out, diffResult);
	printf("\n");
}

void A_A(FILE *out, BigInteger A, BigInteger B)
{ //A-A
	BigInteger diffResult = diff(A, A);
	printBigInteger(out, diffResult);
	printf("\n");
}

void A3_B2(FILE *out, BigInteger A, BigInteger B)
{ //3A-2B
	BigInteger A3 = prod(stringToBigInteger("+3"), A);
	BigInteger B2 = prod(stringToBigInteger("+2"), B);
	BigInteger result = diff(A3, B2);
	printBigInteger(out, result);
	printf("\n");
}

void AB(FILE *out, BigInteger A, BigInteger B)
{ //AB
	BigInteger prodResult = prod(A, B);
	printBigInteger(out, prodResult);
	printf("\n");
}

void AA(FILE *out, BigInteger A, BigInteger B)
{ //A*A
	BigInteger prodResult = prod(A, A);
	printBigInteger(out, prodResult);
	printf("\n");
}

void BB(FILE *out, BigInteger A, BigInteger B)
{ //B*B
	BigInteger prodResult = prod(B, B);
	printBigInteger(out, prodResult);
	printf("\n");
}

void A94xB165(FILE *out, BigInteger A, BigInteger B)
{ //9*A^4+16*B^5
	BigInteger AA = prod(A, A);
	BigInteger AAAA = prod(AA, AA);
	BigInteger A9_4 = prod(AAAA, stringToBigInteger("+3"));

	BigInteger BB = prod(B, B);
	BigInteger BBBB = prod(BB, BB);
	BigInteger BBBBB = prod(BBBB, B);
	BigInteger B16_5 = prod(BBBBB, stringToBigInteger("+16"));
	BigInteger sumResult = sum(A9_4, B16_5);
	printBigInteger(out, sumResult);
	printf("\n");
}

//=======================================

int main(int argc, char *argv[])
{
	int count = 0, i;
	int *lineLength;
	char c = '0';
	char **input;
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

	// allocate backup storage for input file by using the length obtained earlier
	input = malloc((count + 1) * sizeof(char *));
	c = 0;
	for (i = 0; i < count + 1; i++)
	{
		if (i < count)
		{
			input[i] = calloc(lineLength[i] + 1, sizeof(char));
			fgets(input[i], lineLength[i] + 1, in);
			// printf("%s is stored\n", input[i]);
		}
		else if (i == count)
			input[i] = NULL;
	}

	// char sInt1[] = "+999999";
	// char sInt2[] = "-123456789";
	BigInteger A = stringToBigInteger(input[1]);
	BigInteger B = stringToBigInteger(input[3]);

	printBigInteger(stdout, A);
	printf("\n");
	printBigInteger(stdout, B);
	printf("\n");

	AsB(out, A, B);
	A_B(out, A, B);
	A_A(out, A, B);
	A3_B2(out, A, B);
	AB(out, A, B);
	AA(out, A, B);
	BB(out, A, B);
	A94xB165(out, A, B);

	// ----- frees -----
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
	lineLength = NULL;
	input = NULL;
	fclose(in);
	fclose(out);
	freeBigInteger(&A);
	freeBigInteger(&B);
	return 0;
}
