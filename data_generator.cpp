#include <iostream>
#include <fstream>
#include <random>

int main() {
    // Open an output file stream to write the generated data
    std::ofstream outfile("data.txt");
    if (!outfile.is_open()) {
        std::cerr << "Failed to open output file!" << std::endl;
        return 1;
    }

    // Define parameters
    const int NUM_VALUES = 1000000;     // Number of random integers to generate
    const int MIN_VALUE = 0;            // Minimum random value
    const int MAX_VALUE = 1000;         // Maximum random value

    // Initialize random number generator
    std::random_device rd;
    std::mt19937 gen(rd());                             // Mersenne Twister engine
    std::uniform_int_distribution<> dist(MIN_VALUE, MAX_VALUE);  // Uniform distribution

    // Generate and write random integers
    for (int i = 0; i < NUM_VALUES; ++i) {
        outfile << dist(gen) << "\n";
    }

    // Close the file
    outfile.close();
    std::cout << "Data generation completed. Output written to data.txt" << std::endl;

    return 0;
}