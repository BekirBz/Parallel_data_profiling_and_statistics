#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <mpi.h>

const int MAX_VALUE = 1000;
const int HISTOGRAM_BINS = 10; // Show only first 10 values in summary

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    std::vector<int> values;
    int total_elements = 0;

    if (rank == 0) {
        // Only rank 0 reads the file
        std::ifstream infile("data.txt");
        int number;
        while (infile >> number) {
            values.push_back(number);
        }
        infile.close();
        total_elements = values.size();
    }

    // Broadcast number of elements
    MPI_Bcast(&total_elements, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Resize and scatter data
    int chunk_size = total_elements / size;
    std::vector<int> local_values(chunk_size);
    MPI_Scatter(values.data(), chunk_size, MPI_INT, local_values.data(), chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Start timing (only rank 0 will print it)
    auto start_time = std::chrono::high_resolution_clock::now();

    // Compute local sum
    double local_sum = 0.0;
    for (int val : local_values)
        local_sum += val;

    // Reduce all local sums into global sum
    double global_sum = 0.0;
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    double mean = 0.0;
    if (rank == 0)
        mean = global_sum / total_elements;

    // Broadcast mean
    MPI_Bcast(&mean, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Compute local variance sum
    double local_variance_sum = 0.0;
    for (int val : local_values)
        local_variance_sum += (val - mean) * (val - mean);

    // Reduce all variance sums
    double global_variance_sum = 0.0;
    MPI_Reduce(&local_variance_sum, &global_variance_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    // Local histogram (first 10 values only)
    std::vector<int> local_histogram(HISTOGRAM_BINS, 0);
    for (int val : local_values) {
        if (val < HISTOGRAM_BINS)
            local_histogram[val]++;
    }

    // Global histogram
    std::vector<int> global_histogram(HISTOGRAM_BINS, 0);
    MPI_Reduce(local_histogram.data(), global_histogram.data(), HISTOGRAM_BINS, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end_time - start_time;

    if (rank == 0) {
        std::cout << "Total elements: " << total_elements << std::endl;
        std::cout << "Mean: " << mean << std::endl;
        std::cout << "Variance: " << global_variance_sum / total_elements << std::endl;
        std::cout << "Execution time (MPI): " << duration.count() << " seconds" << std::endl;
        std::cout << "Histogram summary (first 10 values):" << std::endl;
        for (int i = 0; i < HISTOGRAM_BINS; ++i)
            std::cout << "Value " << i << ": " << global_histogram[i] << " times" << std::endl;
    }

    MPI_Finalize();
    return 0;
}