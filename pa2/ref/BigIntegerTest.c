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

	char sInt1[] = "+9876543";
	char sInt2[] = "-123456789";
	BigInteger N1 = stringToBigInteger(sInt1);
	BigInteger N2 = stringToBigInteger(sInt2);
	printBigInteger(stdout, N1);
	printf("\n");
	printBigInteger(stdout, N2);
	printf("\n");
	
	printf("%d %d %d\n", sign(N1), sign(N2), sign(N)); 
	
	printf("%d %d %d\n", compare(N1,N2), compare(N2,N1), compare(N1,N1));
	
//	printf("%d %d \n", equals(N1,N2), equals(N1,N1));

	BigInteger copyN1 = copy(N1);
	printBigInteger(stdout, copyN1);
	printf("\n");
	
	BigInteger sumResult = sum(N1,N2);
	BigInteger diffResult = diff(N1,N2);
	BigInteger prodResult = prod(N1,N2);
	printBigInteger(stdout, sumResult);
	printf("\n");
	printBigInteger(stdout, diffResult);
	printf("\n");
	printBigInteger(stdout, prodResult);
	printf("\n");
	
	add(N,N1,N2);
	printBigInteger(stdout, N);
	printf("\n");
	
	subtract(N,N1,N2);
	printBigInteger(stdout, N);
	printf("\n");
	
	multiply(N,N1,N2);
	printBigInteger(stdout, N);
	printf("\n");
    puts("----------TEST END----------");

    return 0;
}