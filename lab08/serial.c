#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10000000  

int main() {
    float *A, *B, *C;
    A = (float*) malloc(SIZE * sizeof(float));
    B = (float*) malloc(SIZE * sizeof(float));
    C = (float*) malloc(SIZE * sizeof(float));

   
    for (size_t i = 0; i < SIZE; i++) {
        A[i] = 1.0f;
        B[i] = 2.0f;
    }

    clock_t start = clock();

    
    for (size_t i = 0; i < SIZE; i++) {
        C[i] = A[i] + B[i];
    }

    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Serial Execution Time: %f seconds\n", time_taken);

    
    free(A);
    free(B);
    free(C);

    return 0;
}
