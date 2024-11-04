#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10000000

void sequential_loop(int* a, int* b, int* c, int n) {
    for (int i = 1; i < n; i++) {
        a[i] = a[i-1] + b[i];  // Loop-carried dependency
        c[i] = 2 * b[i];       // Independent operation
    }
}

void parallel_loop(int* a, int* b, int* c, int n) {
    // First loop with dependency
    for (int i = 1; i < n; i++) {
        a[i] = a[i-1] + b[i];
    }

    // Second loop, potentially parallelizable
    for (int i = 1; i < n; i++) {
        c[i] = 2 * b[i];
    }
}

double get_time() {
    return (double)clock() / CLOCKS_PER_SEC;
}

int main() {
    int *a = malloc(SIZE * sizeof(int));
    int *b = malloc(SIZE * sizeof(int));
    int *c = malloc(SIZE * sizeof(int));

    if (!a || !b || !c) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Initialize arrays
    for (int i = 0; i < SIZE; i++) {
        a[i] = 0;
        b[i] = i;
        c[i] = 0;
    }

    double start, end;

    // Sequential version
    start = get_time();
    sequential_loop(a, b, c, SIZE);
    end = get_time();
    printf("Sequential time: %f seconds\n", end - start);

    // Reset arrays
    for (int i = 0; i < SIZE; i++) {
        a[i] = 0;
        c[i] = 0;
    }

    // Parallel version (note: not actually parallel in this implementation)
    start = get_time();
    parallel_loop(a, b, c, SIZE);
    end = get_time();
    printf("'Parallel' time: %f seconds\n", end - start);

    free(a);
    free(b);
    free(c);

    return 0;
}