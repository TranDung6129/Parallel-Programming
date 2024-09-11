#include <iostream>
#include <vector>
#include <omp.h>
#include <limits>
#include <ctime>

// Function to find the largest value in an array sequentially
double findLargestSequential(const std::vector<double>& arr) {
    double max_val = std::numeric_limits<double>::min();
    for (double val : arr) {
        if (val > max_val) {
            max_val = val;
        }
    }
    return max_val;
}

// Function to find the largest value in an array using OpenMP
double findLargestParallel(const std::vector<double>& arr) {
    double max_val = std::numeric_limits<double>::min();
    #pragma omp parallel for reduction(max:max_val)
    for (int i = 0; i < arr.size(); ++i) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }
    return max_val;
}

int main() {
    const int size = 100000000; // Size of the array
    std::vector<double> array(size);

    // Initialize array with random values
    for (int i = 0; i < size; ++i) {
        array[i] = static_cast<double>(rand()) / RAND_MAX * 1000; // Random values between 0 and 1000
    }

    // Sequential calculation and time measurement
    double start_time_seq = omp_get_wtime();
    double largest_seq = findLargestSequential(array);
    double end_time_seq = omp_get_wtime();
    std::cout << "Sequential Largest Value: " << largest_seq << std::endl;
    std::cout << "Sequential Execution Time: " << end_time_seq - start_time_seq << " seconds" << std::endl;

    // Parallel calculation and time measurement
    double start_time_parallel = omp_get_wtime();
    double largest_parallel = findLargestParallel(array);
    double end_time_parallel = omp_get_wtime();
    std::cout << "Parallel Largest Value: " << largest_parallel << std::endl;
    std::cout << "Parallel Execution Time: " << end_time_parallel - start_time_parallel << " seconds" << std::endl;

    return 0;
}
