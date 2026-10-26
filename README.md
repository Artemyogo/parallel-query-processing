# Parallel Query Processing

Course project for Concurrent Programming at the Theoretical Computer Science department, Jagiellonian University.
It answers many offline range-counting queries and compares a single-threaded baseline with two
multithreaded C++20 versions: `std::thread` and OpenMP.

## Problem

Chestnut trees grow along a street. The gaps between consecutive trees are `d1, d2, ..., dk` metres,
measured from the western end, and a gap can be 0. For each of `q` queries `a`, the task is to count the
trees within the first `a` metres of the street, i.e. the trees that would be cut down to build a
hypermarket there.

## Approach

1. Build prefix sums of `d` to get each tree's position.
2. Sort the queries and sweep them against the positions with **two pointers**. In benchmarks this was
   1.5–2× faster than running a binary search for each query, both single-threaded and multithreaded.
3. Sorting all queries was the bottleneck, so the parallel versions **split the queries into one chunk
   per thread**. Each thread sorts only its own chunk and runs its own two-pointer sweep.

| File | Description |
|------|-------------|
| `src/slow.cpp` | Single-threaded baseline |
| `src/fast_thread.cpp` | Parallel version using `std::thread` (one chunk per hardware thread) |
| `src/fast_openmp.cpp` | Parallel version using an OpenMP parallel region |
| `src/gen.cpp` | Random test data generator |
| `src/test.cpp` | Benchmark harness that times every version and checks results against the baseline |

## Results

Running time in ms, with `k = q`:

**Laptop**: up to ~7× speedup

| Input size | Single-threaded | std::thread | OpenMP |
|-----------:|----------------:|------------:|-------:|
| 1×10⁶ | 181 | 27 | 29 |
| 1×10⁷ | 2037 | 316 | 329 |
| 5×10⁷ | 11118 | 1612 | 1588 |

**Server (student.tcs.uj.edu.pl)**: up to ~20× speedup

| Input size | Single-threaded | std::thread | OpenMP |
|-----------:|----------------:|------------:|-------:|
| 1×10⁶ | 288 | 52 | 97 |
| 1×10⁷ | 3369 | 325 | 318 |
| 5×10⁷ | 19547 | 1044 | 938 |

The full report (in Polish) is in [`report.pdf`](report.pdf).

## Build & run

You need CMake ≥ 3.16, a C++20 compiler with OpenMP support, and GCC (the code includes `<bits/stdc++.h>`).

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/test [k] [q]   # defaults: k = q = 10^7
```
