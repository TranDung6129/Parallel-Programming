#include "myLib.h"
#include <iostream>
#include <vector>
#include <omp.h>
#include <stdexcept>

void matrixVectorMultiplication(const std::vector<std::vector<double>>& matrix, const std::vector<double>& vector, std::vector<double>& result) {
    int numRows = matrix.size();
    int numCols = matrix[0].size();
    int vectorSize = vector.size();

    if (numCols != vectorSize) {
        throw std::invalid_argument("Matrix columns must be equal to vector size for multiplication.");
    }

    #pragma omp parallel for shared(matrix, vector, result)
    for (int i = 0; i < numRows; ++i) {
        double sum = 0.0;
        #pragma omp simd reduction(+:sum)
        for (int j = 0; j < numCols; ++j) {
            sum += matrix[i][j] * vector[j];
        }
        result[i] = sum;
    }
}

int main() {
    try {
        std::vector<std::vector<double>> matrix = readMatrixFromFile("../input/matrix.txt");
        std::vector<double> vector = readVectorFromFile("../input/vector.txt");

        std::vector<double> result(matrix.size());

        matrixVectorMultiplication(matrix, vector, result);

        std::cout << "Result: ";
        for (double val : result) {
            std::cout << val << " ";
        }
        std::cout << std::endl;

    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    return 0;
}
