#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
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

    auto start = std::chrono::high_resolution_clock::now(); // Start timing

    // Compute mean
    double sum = 0.0;
    for (int val : values) {
        sum += val;
    }
    mean = sum / n;

    // Compute variance
    double variance_sum = 0.0;
    for (int val : values) {
        variance_sum += (val - mean) * (val - mean);
    }
    variance = variance_sum / n;

    // Compute histogram (0–1000)
    const int HIST_SIZE = 1001;
    std::vector<int> histogram(HIST_SIZE, 0);
    for (int val : values) {
        if (val >= 0 && val <= 1000) {
            histogram[val]++;
        }
    }

    auto end = std::chrono::high_resolution_clock::now(); // End timing
    std::chrono::duration<double> duration = end - start;

    // Output results
    std::cout << "Total elements: " << n << std::endl;
    std::cout << "Mean: " << mean << std::endl;
    std::cout << "Variance: " << variance << std::endl;
    std::cout << "Execution time (Sequential): " << duration.count() << " seconds" << std::endl;

    // Optional: Output histogram summary
    std::cout << "Histogram summary (first 10 values):" << std::endl;
    for (int i = 0; i < 10; ++i) {
        std::cout << "Value " << i << ": " << histogram[i] << " times" << std::endl;
    }

    return 0;
}