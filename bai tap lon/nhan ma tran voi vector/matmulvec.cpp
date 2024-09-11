#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

// Function to allocate memory for a matrix
double **allocateMatrix(int rows, int cols) {
    double **matrix = (double **)malloc(rows * sizeof(double *));
    if (matrix == NULL) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < rows; i++) {
        matrix[i] = (double *)malloc(cols * sizeof(double));
        if (matrix[i] == NULL) {
            printf("Memory allocation failed!\n");
            exit(EXIT_FAILURE);
        }
    }

    return matrix;
}

// Function to free memory allocated for a matrix
void freeMatrix(double **matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Function to perform matrix-vector multiplication sequentially
double *matrixVectorMultiplySeq(double **matrix, double *vector, int rows, int cols) {
    double *result = (double *)malloc(rows * sizeof(double));
    if (result == NULL) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < rows; i++) {
        result[i] = 0.0;
        for (int j = 0; j < cols; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }

    return result;
}

// Function to perform matrix-vector multiplication in parallel
double *matrixVectorMultiplyParallel(double **matrix, double *vector, int rows, int cols) {
    double *result = (double *)malloc(rows * sizeof(double));
    if (result == NULL) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    #pragma omp parallel for
    for (int i = 0; i < rows; i++) {
        result[i] = 0.0;
        for (int j = 0; j < cols; j++) {
            result[i] += matrix[i][j] * vector[j];
        }
    }

    return result;
}

// Function to display generated matrix and vector
void display_matandvec(double **matrix, double *vector, int rows, int cols) {
    printf("Generated Matrix:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%.2f ", matrix[i][j]);
        }
        printf("\n");
    }

    printf("Generated Vector:\n");
    for (int i = 0; i < rows; i++) {
        printf("%.2f ", vector[i]);
    }
    printf("\n");
}

int main() {
    srand(time(NULL)); // Seed for random number generation

    int rows = 15000; // Number of rows in the matrix
    int cols = 15000; // Number of columns in the matrix

    // Dynamically allocate memory for the matrix
    double **matrix = allocateMatrix(rows, cols);

    // Dynamically allocate memory for the vector
    double *vector = (double *)malloc(cols * sizeof(double));
    if (vector == NULL) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    // Generate random values for matrix and vector
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matrix[i][j] = (double)(rand() % 100) / 10.0; // Random values between 0 and 10 (example)
        }
        vector[i] = (double)(rand() % 100) / 10.0; // Random values between 0 and 10 (example)
    }

    // Display the generated matrix
    // display_matandvec(matrix, vector, rows, cols);

    double start_time_seq = omp_get_wtime(); // Start measuring time for sequential execution

    // Perform matrix-vector multiplication sequentially
    double *result_seq = matrixVectorMultiplySeq(matrix, vector, rows, cols);

    double end_time_seq = omp_get_wtime(); // End measuring time for sequential execution
    double execution_time_seq = end_time_seq - start_time_seq; // Calculate execution time for sequential execution

    double start_time_parallel = omp_get_wtime(); // Start measuring time for parallel execution

    // Perform matrix-vector multiplication in parallel
    double *result_parallel = matrixVectorMultiplyParallel(matrix, vector, rows, cols);

    double end_time_parallel = omp_get_wtime(); // End measuring time for parallel execution
    double execution_time_parallel = end_time_parallel - start_time_parallel; // Calculate execution time for parallel execution

    // Display the results and execution times
    // printf("Sequential Result of matrix-vector multiplication:\n");
    // for (int i = 0; i < rows; i++) {
    //     printf("%.2f ", result_seq[i]);
    // }
    printf("\nSequential Execution Time: %f seconds\n\n", execution_time_seq);

    // printf("Parallel Result of matrix-vector multiplication:\n");
    // for (int i = 0; i < rows; i++) {
    //     printf("%.2f ", result_parallel[i]);
    // }
    printf("\nParallel Execution Time: %f seconds\n", execution_time_parallel);

    // Free dynamically allocated memory
    freeMatrix(matrix, rows);
    free(vector);
    free(result_seq);
    free(result_parallel);

    return 0;
}
