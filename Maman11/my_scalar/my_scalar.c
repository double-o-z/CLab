#include <stdio.h>
#define MAX_VECTOR 100

/* scalar_product: iterate over vec1 and vec2 integer arrays,
 * and sum the product of the multiplication of their items.
 * return integer: (vec1[0]* vec2[0] + ... + vec1[len-1] * vec2[len-1]).
 * */
int scalar_product(int vec1[], int vec2[], int len){
    int product, i;
    for (product = 0, i = 0; i < len; i++){
        product += vec1[i] * vec2[i];
    }
    printf("Scalar product of these vectors: %d\n", product);
    return product;
}

/* This program gets a length for vectors, and two vectors with integer values.
 * Then calculates and returns the scalar product of these vectors.
 * Example:
 * length: 4
 * vector 1: [1, -2, 3, -4]
 * vector 2: [6, 7, 1, -2]
 * Result:
 * 3
 * */
int main(){
    int len;
    int i, vec1[MAX_VECTOR], vec2[MAX_VECTOR];\
    printf("Please input integer size for scalar_product function:\n");
    scanf("%d", &len);

    printf("Please input first vector of integer numbers, separated by spaces or newlines.\n");
    for (i = 0; i < len; i++)
        scanf("%d", &vec1[i]);
    printf("Please input second vector of integer numbers, separated by spaces or newlines.\n");
    for (i = 0; i < len; i++)
        scanf("%d", &vec2[i]);

    /* Calculate vectors product and returns an integer value. */
    return scalar_product(vec1, vec2, len);
}
