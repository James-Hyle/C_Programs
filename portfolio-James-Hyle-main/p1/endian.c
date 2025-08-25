#include <stdio.h>

void recPrint(unsigned int x);
void printBits(unsigned int x);
unsigned char isBitSet(unsigned int ch, int i);
unsigned char getBits(unsigned int x, int p, int n);
unsigned int swapBytes(unsigned int x);
int main(void);

// just for fun
void recPrint(unsigned int x) {
    if (x > 0) { // Base case
        recPrint(x / 2); // check if x is divisible by 2
        printf("%d", x % 2); // ? bit is set or not
    }
}

// print bits of value ~ should be 32 bits long
void printBits(unsigned int x) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", isBitSet(x, i));
    }
}

// check if bit at i is 1 or 0
unsigned char isBitSet(unsigned int ch, int i) {
    unsigned int mask = 1 << i;

    return (ch & mask) ? 1 : 0;
}

// from K & R - getbits(x,4,3) returns the three bits in x at positions 4, 3 and 2, right-adjusted
unsigned char getBits(unsigned int x, int p, int n) {
    return (x >> (p - n + 1)) & ~(~0U << n);
}

// set bit using bitwise or
unsigned char setBits(char ch, int i) {
    unsigned char mask = 1 << i;

    return mask | ch;
}

// reverse endianness of unsigned int x
unsigned int swapBytes(unsigned int x) {
    unsigned int n = 0;

    for (int i = 0; i < 4; i++) {
        unsigned int byte = getBits(x, 31 - (8 * i), 8);
        n |= setBits(byte, 8) << (8 * i);
    }

    return n;
}

// main ~ pass in positive int value from command line
int main(void) {
    unsigned int x = 0;
    scanf("%u", &x); // user enters number to be endianess-swapped
    printf("Decimal         Binary                              Hexadecimal\n");
    printf("----------------------------------------------------------------\n");
    printf("x  %-9u    ", x);
    printBits(x);
    printf("   0x%08x\n", x);
    printf("x' %-9u    ", swapBytes(x));
    printBits(swapBytes(x));
    printf("   0x%08x\n", swapBytes(x));

    return 0;
}