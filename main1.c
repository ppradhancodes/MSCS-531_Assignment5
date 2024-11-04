#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <xmmintrin.h> // SSE

#define SIZE 1024

void scalar_add(float *a, float *b, float *c, int size) {
    for (int i = 0; i < size; i++) {
        c[i] = a[i] + b[i];
    }
}

void simd_add(float *a, float *b, float *c, int size) {
    for (int i = 0; i < size; i += 4) {
        __m128 va = _mm_loadu_ps(&a[i]); // Use unaligned load
        __m128 vb = _mm_loadu_ps(&b[i]); // Use unaligned load
        __m128 vc = _mm_add_ps(va, vb);
        _mm_storeu_ps(&c[i], vc); // Use unaligned store
    }
}

int main() {
    float *a = (float*)malloc(SIZE * sizeof(float));
    float *b = (float*)malloc(SIZE * sizeof(float));
    float *c = (float*)malloc(SIZE * sizeof(float));

    if (!a || !b || !c) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Initialize arrays
    for (int i = 0; i < SIZE; i++) {
        a[i] = (float)rand() / RAND_MAX;
        b[i] = (float)rand() / RAND_MAX;
    }

    // Scalar addition
    clock_t start = clock();
    scalar_add(a, b, c, SIZE);
    clock_t end = clock();
    double scalar_time = (double)(end - start) / CLOCKS_PER_SEC;

    // SIMD addition
    start = clock();
    simd_add(a, b, c, SIZE);
    end = clock();
    double simd_time = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Scalar time: %f seconds\n", scalar_time);
    printf("SIMD time: %f seconds\n", simd_time);
    printf("Speedup: %.2fx\n", scalar_time / simd_time);

    free(a);
    free(b);
    free(c);
    return 0;
}