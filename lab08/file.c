#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define SIZE 10000000  // 10 million elements
#define NUM_THREADS 10

typedef struct {
    float *A, *B, *C;
    size_t start, end;
} ThreadData;

void* add_arrays(void* arg) {
    ThreadData* data = (ThreadData*) arg;
    for (size_t i = data->start; i < data->end; i++) {
        data->C[i] = data->A[i] + data->B[i];
    }
    return NULL;
}

int main() {
    float *A, *B, *C;
    A = (float*) malloc(SIZE * sizeof(float));
    B = (float*) malloc(SIZE * sizeof(float));
    C = (float*) malloc(SIZE * sizeof(float));

    for (size_t i = 0; i < SIZE; i++) {
        A[i] = 1.0f;
        B[i] = 2.0f;
    }

    pthread_t threads[NUM_THREADS];
    ThreadData thread_data[NUM_THREADS];
    size_t chunk_size = SIZE / NUM_THREADS;

    clock_t start = clock();

    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].A = A;
        thread_data[i].B = B;
        thread_data[i].C = C;
        thread_data[i].start = i * chunk_size;
        thread_data[i].end = (i == NUM_THREADS - 1) ? SIZE : (i + 1) * chunk_size;

        pthread_create(&threads[i], NULL, add_arrays, &thread_data[i]);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Parallel Execution Time with %d threads: %f seconds\n", NUM_THREADS, time_taken);

    free(A);
    free(B);
    free(C);

    return 0;
}
