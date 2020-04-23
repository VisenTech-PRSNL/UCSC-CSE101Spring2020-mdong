//-----------------------------------------------------------------------------
// BigInteger.c
// source code library for the BigInteger ADT
//-----------------------------------------------------------------------------

#include "BigInteger.h"
#include "List.h"

#define smaller -1
#define larger 1
#define equal 0

typedef struct BigIntegerObj
{
    int sign;
    List magnitude;
} BigIntegerObj;
List strToList(char *str, int initIndex);
char *strrev(char *str);
////////////////////
// private functions
////////////////////
List addition(List A, List B);
List intersection(List A, List B);
List times(List A, List B);
List listTimesDigit(List A, long x);
List strToList(char *s, int sIndex);
List listTrim(List A);
int compareList(List A, List B);
long privateStringToLong(char *ss);
int countDown(List A);
List absolute(BigInteger A);
long pow(long A, long B);
///////////////////////////////////////////////////////////////////////////////
// Constructors-Destructors ---------------------------------------------------
///////////////////////////////////////////////////////////////////////////////
BigInteger newBigInteger()
{
    BigInteger new = malloc(sizeof(BigIntegerObj));
    // new->magnitude = newList();
    new->sign = 0;
    return new;
}

void freeBigInteger(BigInteger *pN)
{
    // List target;
    if (pN != NULL && *pN != NULL)
    {
        // if ((*pN)->sign != 0)
        //      target = (*pN)->magnitude;
        // if ((*pN)->sign != 0 && (*pN)->magnitude != NULL)
        freeList(&((*pN)->magnitude));
        free(*pN);
        *pN = NULL;
    }
    else
    {
        fprintf(stderr, "USAGE: freeBigInteger() called on invalid BigInteger\n");
    }
}
int sign(BigInteger N)
{
    assert(N != NULL);
    return N->sign;
}
int compare(BigInteger A, BigInteger B)
{
    assert(A != NULL && B != NULL);
    int compBool = 0;
    // edge cases
    // compare zeros
    if (A->sign == 0 && B->sign == 0)
        return compBool;
    // compare sign
    if (A->sign > B->sign)
        compBool = larger;
    else if (A->sign < B->sign)
        compBool = smaller;
    if (compBool != 0)
        return compBool;

    assert(A->magnitude != NULL && B->magnitude != NULL);
    compBool = compareList(A->magnitude, B->magnitude);
    return compBool;
}
int equals(BigInteger A, BigInteger B)
{
    int result = false;
    if (listEquals(A->magnitude, B->magnitude) && A->sign == B->sign)
        result = true;
    return result;
}
void makeZero(BigInteger N)
{
    assert(N != NULL);
    if (N->sign != 0 && N->magnitude != NULL)
        freeList(&(N->magnitude));
    N->sign = 0;
}
void negate(BigInteger N)
{
    if (N->sign == -1)
        N->sign = 1;
    else if (N->sign == 1)
        N->sign = -1;
}
BigInteger stringToBigInteger(char *s)
{
    if (POWER <= 0)
    {
        fprintf(stderr, "EXCEPTION: SETTING ON POWER IS AN INVALID VALUE\n");
        exit(EXIT_FAILURE);
    }

    BigInteger N = newBigInteger();
    int firstIndex = 0;
    if (s[0] == '-' && strlen(s) > 1)
    {
        N->sign = -1;
        firstIndex = 1;
    }
    else if (s[0] == '0' && strlen(s) == 1)
    {
        N->sign = 0;
        return N;
    }
    else if (s[0] == '+' && strlen(s) > 1)
    {
        N->sign = 1;
        firstIndex = 1;
    }
    else if (strlen(s) > 0)
    {
        N->sign = 1;
        firstIndex = 0;
    }
    else
    {
        fprintf(stderr, "USAGE: stringToBigInteger() call on invalid string\n");
        exit(EXIT_FAILURE);
    }

    N->magnitude = strToList(s, firstIndex);
    return N;
}
BigInteger copy(BigInteger N)
{
    assert((N != NULL && N->magnitude != NULL) && "USAGE: copy() call on uninitalized BigInteger");
    BigInteger new = newBigInteger();
    new->magnitude = copyList(N->magnitude);
    new->sign = N->sign;
    return new;
}
void add(BigInteger S, BigInteger A, BigInteger B)
{
    assert(A != NULL && B != NULL);
    assert((S != NULL) && "ERROR: add() called with non-created target");
    // assert(A->sign != 0 && B->sign != 0);
    makeZero(S);
    switch (A->sign == B->sign)
    {
    case true: // normal addition, same sign
        // printBigInteger(stdout, A);
        // printf(" + ");
        // printBigInteger(stdout, B);
        // printf(" = ");
        S->sign = A->sign;
        if (S->sign != 0)
            S->magnitude = addition(A->magnitude, B->magnitude);
        break;
    case false: // addition for different sign, equivalent to subtraction
        // printf("compare result : %d\n", compareList(A->magnitude, B->magnitude));
        switch (compareList(A->magnitude, B->magnitude))
        {
        case equal:
            // printf("A = B: A + B = ");
            S->sign = 0;
            break;
        case larger:
            // printf("A - B = ");
            S->sign = A->sign;
            S->magnitude = intersection(A->magnitude, B->magnitude);
            break;
        case smaller:
            // printf("B - A = ");
            S->sign = B->sign;
            S->magnitude = intersection(B->magnitude, A->magnitude);
            break;
        }
        break;
    }
}
BigInteger sum(BigInteger A, BigInteger B)
{
    assert(A != NULL && B != NULL);
    assert((A->sign != 0 && B->sign != 0) && "EXCEPTION: sum() call on invalid BigInteger");
    BigInteger N = (BigInteger)malloc(sizeof(BigIntegerObj));
    add(N, A, B);
    return N;
}

void subtract(BigInteger D, BigInteger A, BigInteger B)
{
    assert(A != NULL && B != NULL);
    assert((D != NULL) && "ERROR: subtract() called with non-created target");
    // assert(A->sign != 0 && B->sign != 0);
    makeZero(D);
    switch (A->sign == B->sign)
    {
    case false: // subtraction between different sign doesn't change sign
        // printBigInteger(stdout, A);
        // printf(" - ");
        // printBigInteger(stdout, B);
        // printf(" = ");
        D->sign = A->sign;
        if (D->sign != 0)
            D->magnitude = addition(A->magnitude, B->magnitude);
        break;
    case true: // subtraction for same sign, equivalent to addition
        // printf("A compares B: %d\n", compareList(A->magnitude, B->magnitude));
        if (A->sign != 0 && B->sign != 0)
        {
            // printf("compare result : %d\n", compareList(A->magnitude, B->magnitude));
            switch (compareList(A->magnitude, B->magnitude))
            {
            case equal:
                // printf("A = B: A - (-B) = ");
                D->sign = 0;
                break;
            case larger:
                // printf("A - (-B) = ");
                D->sign = A->sign;
                D->magnitude = intersection(A->magnitude, B->magnitude);
                break;
            case smaller:
                // printf("B - (-A) = ");
                D->sign = B->sign;
                negate(D);
                D->magnitude = intersection(B->magnitude, A->magnitude);
                break;
            }
        }
        else if (A->sign != 0 && B->sign == 0)
        {
            D = copy(A);
        }
        else if (A->sign == 0 && B->sign != 0)
        {
            D = copy(B);
            negate(D);
        }
        else if (A->sign == 0 && B->sign == 0)
        {
            makeZero(D);
        }
        break;
    }
}
BigInteger diff(BigInteger A, BigInteger B)
{
    assert(A != NULL && B != NULL);
    assert((A->sign != 0 && B->sign != 0) && "EXCEPTION: diff() call on invalid BigInteger");
    BigInteger N = (BigInteger)malloc(sizeof(BigIntegerObj));
    subtract(N, A, B);
    return N;
}
void multiply(BigInteger P, BigInteger A, BigInteger B)
{
    makeZero(P);
    BigInteger copyA = copy(A);
    BigInteger copyB = copy(B);
    if (copyA->sign == 0 || copyB->sign == 0)
        P->sign = 0;
    else if (copyA->sign == copyB->sign)
        P->sign = 1;
    else
        P->sign = -1;
    // printf("multiply(): sign result = %d\n", P->sign);
    switch (compareList(A->magnitude, B->magnitude))
    {
    case -1:
        // printBigInteger(stdout, B);
        // printf(" * ");
        // printBigInteger(stdout, A);
        // printf(": \n");
        P->magnitude = times(copyB->magnitude, copyA->magnitude);
        break;
    default:
        // printBigInteger(stdout, A);
        // printf(" * ");
        // printBigInteger(stdout, B);
        // printf(": \n");
        P->magnitude = times(copyA->magnitude, copyB->magnitude);
        break;
    }

    // moveFront(P->magnitude);
    // if (length(P->magnitude) == 1 && get(P->magnitude) == 0)
    //     P->sign = 0;

    freeBigInteger(&copyA);
    freeBigInteger(&copyB);
}
BigInteger prod(BigInteger A, BigInteger B)
{
    assert(A != NULL && B != NULL);
    BigInteger N = newBigInteger();
    if (A->sign != 0 && B->sign != 0)
        multiply(N, A, B);
    return N;
}
void printBigInteger(FILE *out, BigInteger N)
{
    assert(out != NULL && N != NULL);
    switch (N->sign)
    {
    case 0:
        fprintf(out, "0");
        break;
    case -1:
        fprintf(out, "-");
        moveFront(N->magnitude);
        while (listIndex(N->magnitude) != -1 && listIndex(N->magnitude) < length(N->magnitude))
        {
            if (listIndex(N->magnitude) == 0)
                fprintf(out, "%ld", get(N->magnitude));
            else
                fprintf(out, "%0*ld", POWER, get(N->magnitude));

            moveNext(N->magnitude);
        }
        break;
    case 1:
        moveFront(N->magnitude);
        while (listIndex(N->magnitude) != -1 && listIndex(N->magnitude) < length(N->magnitude))
        {
            if (listIndex(N->magnitude) == 0)
                fprintf(out, "%ld", get(N->magnitude));
            else
                fprintf(out, "%0*ld", POWER, get(N->magnitude));

            moveNext(N->magnitude);
        }
        break;
    }
}

List strToList(char *s, int sIndex)
{
    // string to magnitude(List)
    // printf("Start to read string from index %d :\n", sIndex);
    int i, j, z;
    int sLength = strlen(s);
    char *buffer;
    List A = newList();
    i = sLength - 1;
    while (i >= sIndex)
    {
        // printf("last index is at %d\n", i);
        if (i > (POWER - 1))
        {
            // puts("TYPE ONE");
            buffer = malloc((POWER + 1) * sizeof(char));
            buffer[POWER] = '\0';
            // let j be the first char of buffer string first
            // increase j until it reaches currently last char i
            // z works as a counter
            for (j = i - POWER + 1, z = 0; j <= i && z < POWER; j++, z++)
            {
                buffer[z] = s[j];
                // fprintf(stdout, "PARSED STRING: %c placed into index %d\n", s[j], z);
            }
            // printf("%s read in\n", buffer);
            prepend(A, (long)atoi(buffer));
            free(buffer);
        }
        else if (i >= sIndex && i < POWER)
        {
            // puts("TYPE TWO");
            // printf("read char from index %d\n%d bytes will be allocated\n", sIndex, i - sIndex + 2);
            buffer = malloc((i - sIndex + 2) * sizeof(char));
            for (j = 0; j < i - sIndex + 1; j++)
                buffer[j] = '0';
            buffer[i - sIndex + 1] = '\0';
            for (j = sIndex, z = 0; j <= i && z <= i - sIndex; j++, z++)
            {
                // printf("cycles %d\n", z + 1);
                buffer[z] = s[j];
                // fprintf(stdout, "PARSED STRING: %c placed into index %d\n", s[j], z);
            }
            prepend(A, privateStringToLong(buffer));
            free(buffer);
        }
        i -= POWER;
    }
    // puts("------String input complete------");
    buffer = NULL;
    return A;
}

long privateStringToLong(char *ss)
{
    // puts("------privateStringToLong------");
    assert(ss != NULL);
    long len = 0;
    long i, j, t, r = 0;
    for (i = 0; ss[i] != '\0'; i++)
        len += 1;
    // printf("String %s has length of %ld\n", ss, len);
    if (len > 0)
    {
        for (i = len - 1, j = 0; i >= 0 && j < len; i--, j++)
        {
            t = (int)ss[i] - '0';
            // printf("%ld read in, ", t);
            t = t * (long)pow((long)10, (long)j);
            // printf("which represents %ld\n", t);
            r += t;
        }
    }
    // puts("------privateStringToLong ENDS------");
    return r;
}

List addition(List A, List B)
{
    List L = newList();
    long overflow = 0, a, b, sum;
    switch (listEquals(A, B))
    {
    case true:
        for (moveBack(A); listIndex(A) >= 0; movePrev(A))
        {
            a = 0;
            if (listIndex(A) >= 0)
                a = get(A);
            sum = a + a + overflow;
            // printf("%d+%d+%d=%d\n",a,b,mod,sum%BASE);
            prepend(L, sum % BASE);
            overflow = sum / (long)BASE;
        }
        if (overflow != 0)
            prepend(L, overflow);
        break;
    case false:
        for (moveBack(A), moveBack(B); listIndex(A) >= 0 || listIndex(B) >= 0; movePrev(A), movePrev(B))
        {
            a = 0;
            b = 0;
            if (listIndex(A) >= 0)
                a = get(A);
            if (listIndex(B) >= 0)
                b = get(B);
            sum = a + b + overflow;
            // printf("%d+%d+%d=%d\n",a,b,mod,sum%BASE);
            prepend(L, sum % BASE);
            overflow = sum / (long)BASE;
        }
        if (overflow != 0)
            prepend(L, overflow);
        break;
    }
    return listTrim(L);
}
List intersection(List A, List B)
{
    // A is larger in absolute value
    List L;
    long carryOut = 0, carryIn = 0, a, b;
    if (length(B) <= 0)
    {
        L = copyList(A);
        return L;
    }
    L = newList();
    for (moveBack(A), moveBack(B); listIndex(A) >= 0 || listIndex(B) >= 0; movePrev(A), movePrev(B))
    {
        a = 0;
        b = 0;
        carryIn = carryOut;
        if (listIndex(A) >= 0)
            a = get(A);
        if (listIndex(B) >= 0)
            b = get(B);
        long sum = a - b + carryIn;
        if (sum < 0)
        {
            sum += BASE;
            carryOut = -1;
        }
        else
            carryOut = 0;
        prepend(L, sum % BASE);
    }
    carryIn = carryOut;
    if (carryIn != 0)
        prepend(L, carryIn);

    return listTrim(L);
}

List listTrim(List A)
{
    // trims out possible zeros read in from calculations
    moveFront(A);
    while (listIndex(A) >= 0 && get(A) == 0)
    {
        if (length(A) > 1)
        {
            deleteFront(A);
            moveFront(A);
        }
        else
            break;
    }
    // if (listIndex(A) == -1)
    // {
    //     clear(A);
    //     append(A, (long)0);
    // }
    return A;
}

int compareList(List A, List B)
{
    assert(A != NULL && B != NULL);
    int compBool = 0;
    // compare length
    if (length(A) > length(B))
        compBool = larger;
    else if (length(A) < length(B))
        compBool = smaller;
    if (compBool != 0)
        return compBool;
    // printf("comparing ");
    // printList(stdout, A);
    // printf(" and ");
    // printList(stdout, B);
    // printf("\n");

    moveFront(A);
    moveFront(B);
    while (listIndex(A) < length(A) && listIndex(B) < length(B) && listIndex(A) >= 0 && listIndex(B) >= 0)
    {
        // printf("bit comparison: %ld | %ld\n", get(A), get(B));
        if (get(A) > get(B))
        {
            compBool = larger;
            break;
        }
        else if (get(A) < get(B))
        {
            compBool = smaller;
            break;
        }
        moveNext(A);
        moveNext(B);
    }
    return compBool;
}

List times(List A, List B)
{

    // BigInteger copyB = copy(B);
    // for (moveBack(B); listIndex(B) >= 0; movePrev(B))
    // {
    //     List L = listTimesDigit(A, get(B));
    //     for (j = 0; j < i; j++)
    //         append(L, 0);
    //     printList(stdout, L);
    //     printf("\n");
    //     // exit(EXIT_SUCCESS);
    //     buffer = addition(sum, L);
    //     freeList(&sum);
    //     sum = buffer;
    //     freeList(&buffer);
    //     i++;
    // }
    List L, P;
    L = newList();
    append(L, 0);
    List multiplyCountDown;
    // printf("frontValue %ld\n", front(B));
    List unit = newList();
    append(unit, 1);
    while (front(B) != (long)0)
    {
        // for (moveBack(A), moveBack(L); listIndex(A) >= 0 || listIndex(L) >= 0; movePrev(A), movePrev(L))
        // {
        //     a = 0;
        //     b = 0;
        //     if (listIndex(A) >= 0)
        //         a = get(A);
        //     if (listIndex(B) >= 0)
        //         b = get(B);
        //     sum = a + b + overflow;
        //     // printf("%d+%d+%d=%d\n",a,b,mod,sum%BASE);
        //     prepend(L, sum % BASE);
        //     overflow = sum / (long)BASE;
        // }
        // if (overflow != 0)
        //     prepend(L, overflow);
        P = addition(A, L);
        // printList(stdout, P);
        // printf("\n");

        freeList(&L);
        L = copyList(P);
        freeList(&P);
        // printList(stdout, L);
        // printf("\n");
        multiplyCountDown = copyList(intersection(B, unit));
        freeList(&B);
        B = copyList(multiplyCountDown);
        freeList(&multiplyCountDown);
    }
    // freeBigInteger(multiplyCountDown);
    // freeBigInteger(copyB);
    // return listTrim(sum);
    freeList(&unit);
    return listTrim(L);
}

List listTimesDigit(List A, long x)
{
    List L = newList();
    long mod = 0;
    for (moveBack(A); listIndex(A) >= 0; movePrev(A))
    {
        long a = 0, sum = 0;
        if (listIndex(A) >= 0)
            a = get(A);
        sum = a * x + mod;
        // printf("%ld * %ld + %ld = %ld\n", a, x, mod, sum);
        prepend(L, sum % BASE);
        mod = sum / BASE;
        // printf("carry out : %ld\n", mod);
    }
    if (mod != 0)
        prepend(L, mod);
    return L;
}

int countDown(List A)
{
    //     long carryOut = 0, carryIn = 0, a, b;
    //     if (length(A) > 0)
    //     {

    //         for (moveBack(A), moveBack(B); listIndex(A) >= 0 || listIndex(B) >= 0; movePrev(A), movePrev(B))
    //         {
    //             a = 0;
    //             b = 0;
    //             carryIn = carryOut;
    //             if (listIndex(A) >= 0)
    //                 a = get(A);
    //             if (listIndex(B) >= 0)
    //                 b = get(B);
    //             long sum = a - 1 + carryIn;
    //             if (sum < 0)
    //             {
    //                 sum += BASE;
    //                 carryOut = -1;
    //             }
    //             else
    //                 carryOut = 0;
    //         }
    //         carryIn = carryOut;
    //         if (carryIn != 0)
    //             prepend(A, carryIn);
    //     return listTrim(A);
    // }
    int resultBoolean = -1;
    List multiplyCountDown;
    List B = copyList(A);
    List unit = newList();
    append(unit, 1);
    while (front(B) != (long)0)
    {
        multiplyCountDown = copyList(intersection(B, unit));
        freeList(&B);
        B = copyList(multiplyCountDown);
        freeList(&multiplyCountDown);
        // printList(stdout, B);
        // printf("  length of %ld", length(B));
        // printf("\n");
    }
    if (front(B) == (long)0)
        resultBoolean = true;
    else
        resultBoolean = false;
    // printf("List countdown cleared\n");
    // freeList(&multiplyCountDown);
    freeList(&B);
    freeList(&unit);
    return resultBoolean;
}

List absolute(BigInteger A)
{
    assert(A != NULL);
    assert(A->magnitude != NULL);
    return A->magnitude;
}

long pow(long A, long B)
{
    double i, j = 1;
    for (i = 0; i < B; i++)
    {
        j *= A;
    }
    return j;
}