#include <stdio.h>

#define BEGIN {
#define END }
#define WAIT(x)                        \
    do                                 \
    {                                  \
        volatile long int z = x * 100; \
        while (z)                      \
        {                              \
            z--;                       \
        }                              \
    } while (0);

#define TEST(x) \
    if (x)      \
    {
#define TSET }
#define ELSE_TEST(x) \
    else if (x)      \
    {
#define TSET_ESLE }
#define OTHERWISE \
    else          \
    {
#define ESIWREHTO }
#define MOD(a, b) (a) % (b)
#define ADD(a, b) (a) + (b)
#define SUB(a, b) (a) - (b)
#define MUL(a, b) (a) * (b)
#define DIV(a, b) (a) / (b)
#define SAY printf
#define ZAHL int
#define PROG(a) \
    int main(void) { a return 0; }

int test(a, b, c) int a;
unsigned int b;
long int c;
{
    return (a & b) ^ c;
}

PROG(
    TEST(15 <= 16)
        SAY("Hallo, Welt\n");
    TSET
        ELSE_TEST(!!0)
            SAY("TEST\n");
    TSET_ESLE
        OTHERWISE
            SAY("Hallo %d\n", MOD(ADD(12, SUB(23, 1)), 13));
    ESIWREHTO
        ZAHL y = 214321543;
    SAY("%d\n", test());
    SAY("y: %d\n", y);
    )
