# Parallel Data Profiling and Statistics

It demonstrates three implementations of statistical profiling on large datasets using different computational paradigms: **Sequential**, **OpenMP**, and **MPI**.

## Project Objective

To compute statistical metrics (mean, variance, and histogram) on a dataset of one million integers using:

- **Sequential Programming**
- **Shared-memory parallelism (OpenMP)**
- **Distributed-memory parallelism (MPI)**

The aim is to **compare performance, efficiency, and scalability** between these methods using profiling techniques.

---

## Features

- Generate synthetic dataset of 1,000,000 random integers (0–1000)
- Compute:
  - Mean (Average)
  - Variance
  - Histogram (Frequency Distribution)
- Implement three versions:
  - `stats_seq.cpp`: Sequential version
  - `stats_openmp.cpp`: OpenMP version
  - `stats_mpi.cpp`: MPI version
- Measure:
  - Execution Time
  - Speedup
  - Efficiency
- Compare performance using visualization and profiling tools

---

## Tech Stack

- Language: **C++**
- Parallel Frameworks:
  - [OpenMP](https://www.openmp.org/)
  - [MPI (MPICH)](https://www.mpich.org/)
- OS: Tested on **macOS** (Apple Silicon)

---

## Folder Structure

```
parallel_stats/
├── data_generator.cpp       # Random integer generator
├── data.txt                 # Generated dataset
├── stats_seq.cpp            # Sequential implementation
├── stats_openmp.cpp         # OpenMP implementation
├── stats_mpi.cpp            # MPI implementation
├── Makefile                 # Compile all versions
├── .gitignore
```

---

## Compilation & Run Instructions

### Prerequisites
- Install g++ with OpenMP support
- Install MPI (e.g., MPICH or OpenMPI)

### Build All
```bash
make all
```

### Run

**Generate data:**
```bash
./data_generator
```

**Run Sequential:**
```bash
./stats_seq
```

**Run OpenMP:**
```bash
./stats_openmp
```

**Run MPI:**
```bash
mpirun -np 14 ./stats_mpi
```

---

## Performance Summary

| Implementation | Execution Time | Speedup | 
|----------------|----------------|---------|
| Sequential     | 0.00673 sec    | 1.0     |
| OpenMP         | 0.01061 sec    | 0.63    |
| MPI (14 proc)  | 0.00149 sec    | 4.5×    |

- **MPI** achieved the best performance.
- **OpenMP** was slower than sequential due to thread management overhead on macOS.

---

## Report

For detailed explanation, design decisions, synchronization strategy, profiling analysis, and future improvements, please refer to the accompanying report:  
📄 `Assignment 3 - Advanced Parallel Algorithm Design and Profiling.pdf`

---

## Future Improvements

- Integrate hybrid MPI + OpenMP model
- Run on more powerful multi-core/multi-node systems
- Use external profiling tools like **gprof**, **Valgrind**, or **Intel VTune**
- Add runtime configuration for data size

---

## Author

**Bekir Bozoklar**  
Course: Multi Core Programming  


