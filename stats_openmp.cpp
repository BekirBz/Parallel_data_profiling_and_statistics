#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <omp.h>
#include <chrono>

int main() {
    std::ifstream infile("data.txt");
    if (!infile.is_open()) {
        std::cerr << "Failed to open data.txt" << std::endl;
        return 1;
    }

    std::vector<int> values;
    int number;

    // Read data from file
    while (infile >> number) {
        values.push_back(number);
    }
    infile.close();

    if (values.empty()) {
        std::cerr << "No data found in file!" << std::endl;
        return 1;
    }

    int n = values.size();
    double mean = 0.0, variance = 0.0;
    const int HIST_SIZE = 1001;
    std::vector<int> histogram(HIST_SIZE, 0);

    auto start = std::chrono::high_resolution_clock::now(); // Start timing

    // Compute mean using OpenMP reduction
    double sum = 0.0;
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; ++i) {
        sum += values[i];
    }
    mean = sum / n;

    // Compute variance using OpenMP reduction
    double variance_sum = 0.0;
    #pragma omp parallel for reduction(+:variance_sum)
    for (int i = 0; i < n; ++i) {
        variance_sum += (values[i] - mean) * (values[i] - mean);
    }
    variance = variance_sum / n;

    // Compute histogram in parallel with atomic updates
    #pragma omp parallel for
    for (int i = 0; i < n; ++i) {
        int val = values[i];
        if (val >= 0 && val <= 1000) {
            #pragma omp atomic
            histogram[val]++;
        }
    }

    auto end = std::chrono::high_resolution_clock::now(); // End timing
    std::chrono::duration<double> duration = end - start;

    // Output results
    std::cout << "Total elements: " << n << std::endl;
    std::cout << "Mean: " << mean << std::endl;
    std::cout << "Variance: " << variance << std::endl;
    std::cout << "Execution time (OpenMP): " << duration.count() << " seconds" << std::endl;

    // Output histogram summary
    std::cout << "Histogram summary (first 10 values):" << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::cout << "Value " << i << ": " << histogram[i] << " times" << std::endl;
    }

    return 0;
}