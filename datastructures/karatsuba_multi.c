#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

uint64_t power(uint64_t number, size_t powerof)
{
    if (powerof == 0)
    {
        return 1;
    }
    return (number * power(number, powerof - 1));
}

char* wrap(char* a, int max)
{
    char* min = a;
    int remaining = max - strlen(min);
    int minlen = strlen(min);

    char* resultme = malloc(max + 1);
    memset(resultme, 0, max + 1);

    size_t i = 0;
    for(i = 0; i < remaining; i++)
    {
        resultme[i] = '0';
    }

    /* printf("added string %s len %d\n", resultme, (int)strlen(resultme)); */
    for (size_t j = 0; j < minlen; j++)
    {
        resultme[i] = min[j];
        i++;
    }
    /* printf("added string %s len %d\n", resultme, (int)strlen(resultme)); */
    return resultme;
}

char* tenPowerChar(int powerof)
{
    char* resultme = malloc(powerof + 2);
    memset(resultme, 0, powerof + 2);

    resultme[0] = '1';
    size_t i;
    for(i = 1; i < powerof + 1; i++)
    {
        resultme[i] = '0';
    }

    resultme[i] = '\0';

    printf("%d power of 10 is %s\n", powerof, resultme);

    return resultme;
}

char* multiplytenpower(char* number, int power)
{
    int numberlen = strlen(number);
    char* resultme = malloc(numberlen + power + 1);
    memset(resultme, 0, numberlen + power + 1);

    size_t i = 0;
    for(i = 0; i < numberlen; i++)
    {
        resultme[i] = number[i];
    }

    /* printf("added string %s len %d\n", resultme, (int)strlen(resultme)); */
    for (size_t j = 0; j < power; j++)
    {
        resultme[i] = '0';
        i++;
    }
    resultme[i] = '\0';
    printf("multiplytenpower %s len %d\n", resultme, (int)strlen(resultme));
    return resultme;
}

void halfTheString(char* from, char** to1, char** to2)
{
    int size = strlen(from);
    int halfsize = strlen(from)/2;
    *to1 = malloc(halfsize + 1);
    *to2 = malloc(halfsize + 1);

    memset(*to1, 0, halfsize+1);
    memset(*to2, 0, halfsize+1);

    memcpy(*to1, from, halfsize);
    memcpy(*to2, &from[halfsize], halfsize);
    (*to1)[halfsize] = '\0';
    (*to2)[halfsize] = '\0';
}

char* subchar(char* a, char* b, int* hand)
{
    int alen = strlen(a);
    int blen = strlen(b);

    printf("sumchar input %s %s sum alen %d blen %d hand %d\n", a, b, alen, blen, *hand);

    int max = alen > blen ? alen : blen;

    if (max <= 2)
    {
        uint64_t sum = atoi(a) + atoi(b) + *hand;
        int carry = 0;
        if ((sum / power(10, max)) != 0)
        {
            *hand = sum / power(10, max);
            sum = sum % power(10, max);
            carry = 1;

            printf("carry over found %d actual return %2lu\n", *hand, sum);
        }
        else
        {
            *hand = 0;
        }
        char* resultme = malloc(max + 1);
        memset(resultme, 0, max + 1);
        sprintf(resultme, "%lu", sum);
        printf("result %s len %d\n", resultme, (int)strlen(resultme));
        if (strlen(resultme) == 1)
            sprintf(resultme, "0%lu", sum);
        else if(strlen(resultme) == 0)
            sprintf(resultme, "00%lu", sum);
        else
            sprintf(resultme, "%lu", sum);
        printf("returning sum %s\n", resultme);
        /* resultme[0] = ' '; */
        return resultme;
    }

    char *c, *d;
    halfTheString(a, &c, &d);
    char *e, *f;
    halfTheString(b, &e, &f);
    printf("halved to %s %s %s %s %s %s\n", a, b, c, d, e, f);

    char* g = subchar(d, f, hand);
    char* h = subchar(c, e, hand);

    printf("---------------------->sum of a %s ,b %s ,hand %d should be %d%s%s\n", a, b, *hand, *hand, h, g);

    int size = max;
    char* resultme = malloc(size + 1);
    memset(resultme, 0, size + 1);
    sprintf(resultme, "%s%s", h, g);

    printf("*&*&*&*&=========================>returning sum %s len %d hand %d\n", resultme, (int)strlen(resultme), *hand);
    return resultme;
}

char* sumchar(char* a, char* b, int* hand)
{
    int alen = strlen(a);
    int blen = strlen(b);

    printf("sumchar input %s %s sum alen %d blen %d hand %d\n", a, b, alen, blen, *hand);

    int max = alen > blen ? alen : blen;

    if (max <= 2)
    {
        uint64_t sum = atoi(a) + atoi(b) + *hand;
        int carry = 0;
        if ((sum / power(10, max)) != 0)
        {
            *hand = sum / power(10, max);
            sum = sum % power(10, max);
            carry = 1;

            printf("carry over found %d actual return %2lu\n", *hand, sum);
        }
        else
        {
            *hand = 0;
        }
        char* resultme = malloc(max + 1);
        memset(resultme, 0, max + 1);
        sprintf(resultme, "%lu", sum);
        printf("result %s len %d\n", resultme, (int)strlen(resultme));
        if (strlen(resultme) == 1)
            sprintf(resultme, "0%lu", sum);
        else if(strlen(resultme) == 0)
            sprintf(resultme, "00%lu", sum);
        else
            sprintf(resultme, "%lu", sum);
        printf("returning sum %s\n", resultme);
        /* resultme[0] = ' '; */
        return resultme;
    }

    char *c, *d;
    halfTheString(a, &c, &d);
    char *e, *f;
    halfTheString(b, &e, &f);
    printf("halved to %s %s %s %s %s %s\n", a, b, c, d, e, f);

    char* g = sumchar(d, f, hand);
    char* h = sumchar(c, e, hand);

    printf("---------------------->sum of a %s ,b %s ,hand %d should be %d%s%s\n", a, b, *hand, *hand, h, g);

    int size = max;
    char* resultme = malloc(size + 1);
    memset(resultme, 0, size + 1);
    sprintf(resultme, "%s%s", h, g);

    printf("*&*&*&*&=========================>returning sum %s len %d hand %d\n", resultme, (int)strlen(resultme), *hand);
    return resultme;
}

char* getSum(char* a, char* b)
{
    int hand = 0;
    int alen = strlen(a);
    int blen = strlen(b);

    int max = alen > blen ? alen : blen;
    char *h = sumchar(a, b, &hand);
    int size = max;
    char* resultme = malloc(size + 1);
    memset(resultme, 0, size + 1);

    if(hand)
        sprintf(resultme, "%d%s", hand, h);
    else
        sprintf(resultme, "%s", h);

    printf("Final sum %s length %d\n", h, (int)strlen(h));

    return resultme;
}

char* wrapAndSum(char* a, char* b)
{
    int alen = strlen(a);
    int blen = strlen(b);
    if (alen == blen)
    {
        return getSum(a, b);
    }

    printf("Wrapping\n");
    int max = alen > blen ? alen : blen;
    char* min = alen > blen ? b : a;
    char* maxme = blen > alen ? b : a;
    int remaining = max - strlen(min);
    int minlen = strlen(min);

    char* resultme = malloc(max + 1);
    memset(resultme, 0, max + 1);

    size_t i = 0;
    for(i = 0; i < remaining; i++)
    {
        resultme[i] = '0';
    }

    /* printf("added string %s len %d\n", resultme, (int)strlen(resultme)); */
    for (size_t j = 0; j < minlen; j++)
    {
        resultme[i] = min[j];
        i++;
    }
    /* printf("added string %s len %d\n", resultme, (int)strlen(resultme)); */

    return getSum(maxme, resultme);
}

char* karatsuba(char* num1, char* num2, int depth)
{
    int num1len = strlen(num1);
    int num2len = strlen(num2);
    int size = num1len;
    int halfsize = size/2;
    if ((num1len << 1) == 0)
        printf("Proper 2 divisible\n");
    else
    {
        printf("not Proper 2 divisible %d\n", num1len);
        uint64_t rem = num1len << (64 - num1len);
        printf("not Proper 2 divisible %u\n", rem);
    }
    printf("karatsuba input %s %s depth %d\n", num1, num2, depth);

    char *a, *b, *c, *d;

    halfTheString(num1, &a, &b);
    halfTheString(num2, &c, &d);

    if (strlen(d) <= 2)
    {
        uint64_t mya = atoi(a);
        uint64_t myb = atoi(b);
        uint64_t myc = atoi(c);
        uint64_t myd = atoi(d);
        uint64_t ac = mya * myc;
        uint64_t bd = myb * myd;
        uint64_t acpbd = ac + bd;

        uint64_t result = (power(10, size) * ac) + (power(10, halfsize) * (((mya + myb) * (myc + myd)) - acpbd)) + bd;
        //printf("a %lu b %lu c %lu d %lu result %lu\n", mya, myb, myc, myd, result);
        char* resultme = malloc(1024);
        memset(resultme, 0, 1024);
        sprintf(resultme, "%lu", result);
        printf("returning %s\n", resultme);
        free((void*)a);
        free((void*)b);
        free((void*)c);
        free((void*)d);
        return resultme;
    }
    char* ac = karatsuba(a, c, depth + 1);
    char* bd = karatsuba(b, d, depth + 1);
    char* apb = wrapAndSum(a, b);
    char* cpd = wrapAndSum(c, d);

    printf("**************************a %s b %s apb %s c %s d %s cpd %s %d %d\n", a, b, apb, c, d, cpd,
           (int)strlen(apb), (int)strlen(cpd));
    char* apbcpd = karatsuba(apb, cpd, depth + 1);
    char* parta = multiplytenpower(ac, size);
    /* printf("parta %s\n", parta); */
    char* partb = multiplytenpower(apbcpd, halfsize);
    char* partc = bd;

    char* partapb = wrapAndSum(parta, partb);
    char* partapbpc = wrapAndSum(partapb, partc);

    printf("**************************a %s b %s apb %s c %s d %s cpd %s %d %d\n", a, b, apb, c, d, cpd,
           (int)strlen(apb), (int)strlen(cpd));
    printf("parta %s partb %s partc %s\n", parta, partb, partc);

    printf("karatsuba result a %s b %s c %s d %s ac %s bd %s depth %d result %s\n", a, b, c, d, ac, bd, depth, partapbpc);
    return partapbpc;
}

int main()
{
    /* char num1[65] = "3141592653589793238462643383279502884197169399375105820974944592"; */
    /* char num2[65] = "2718281828459045235360287471352662497757247093699959574966967627"; */
    /* char num1[65] = "0101010101010101010101010101010101010101010101010101010101010101"; */
    /* char num2[65] = "1010101010101010101010101010101010101010101010101010101010101010"; */
    /* char num2[3] = "9"; */
    char num1[65] = "98765432";
    char num2[65] = "99999999";

    int len1 = strlen(num1);
    int len2 = strlen(num2);

    printf("Input is %s %s\n", num1, num2);
    printf("Len1 %d Len2 %d\n", len1, len2);

    int modlen1 = len1 % 2 ? (len1+1) : len1;
    int modlen2 = len2 % 2 ? (len2+1) : len2;

    printf("modLen1 %d ModLen2 %d\n", modlen1, modlen2);

    karatsuba(num1, num2, 1);
#if 0
    char*h = getSum(num1, num2);
    printf("OMG Final sum %s length %d\n", h, (int)strlen(h));

    /* char num4[9] = "90990909"; */
    /* char num3[6] = "90909"; */
    char *num4 = num1;
    char *num3 = num2;
    char* l = wrapAndSum(num4, num3);
    printf("OMG Final sum of \n %s and \n %s is \n %s length %d\n", num4, wrap(num3, 64), l, (int)strlen(l));

    printf(" tenpower %s\n", tenPowerChar(2));

    char* z = multiplytenpower(num1, 10);
    printf(" multiply power ten %s %d\n", z, (int)strlen(z));
#endif
    return 0;
}
