#include <stdio.h>

/* This program gets two unsigned long numbers from input,
 * and calculates the amount of similar 'turned on' (1) bits.
 * Example:
 * x: 11111001  (249 in decimal)
 * y: 11000011  (193 in decimal)
 * Result:
 * 3
 * */
int main(){
    unsigned long int x, y;
    int i, bitCount, currentBit;

    printf("Please enter two integers, separated by a newline.\n");
    printf("Enter integer X:\n");
    scanf("%lu", &x);
    printf("Received x: %lu\n", x);
    printf("Enter integer Y:\n");
    scanf("%lu", &y);
    printf("Received y: %lu\n", y);

    /* Iterate over both x and y's bits, by using operand & with octal number 1 (01).
     * This allows for comparing of each bit to 1, and then shifting both x and y 1 bit to the right.
     * In this manner we determine for each bit (from right-most to left-most) whether both x and y have 1 in it.
     * If so, we increment bitCount. */
    for (i = 0, bitCount = 0; x != 0 && y != 0; x >>= 1, y >>= 1, i++){
        if ((currentBit = (x & 01)) == 1 && currentBit == (y & 01))
            bitCount++;
    }
    printf("The number of identical 1 bits is: %d\n", bitCount);
    return bitCount;
}
