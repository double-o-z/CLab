#include "mymat.h"

int main() {
    int i, j;
    mat MAT_A, MAT_B, MAT_C, MAT_D, MAT_E, MAT_F;

    for (i = 0; i < 4; ++i) {
        for (j = 0; j < 4; ++j){
            MAT_A.arr[i][j] = 0.0;
            MAT_B.arr[i][j] = 0.0;
            MAT_C.arr[i][j] = 0.0;
            MAT_D.arr[i][j] = 0.0;
            MAT_E.arr[i][j] = 0.0;
            MAT_F.arr[i][j] = 0.0;
        }
    }

    printMat(&MAT_A);
    return 0;
}
