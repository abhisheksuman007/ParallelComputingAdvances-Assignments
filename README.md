Summer-Term-Course : PCA (Parallel Computing : Advances) - Course Content Assignment CUDA

Assignment 1. Write a CUDA code, for a given very large array, and produce the addition of even index elements and odd index elements separately.
              The array can be generated by a random number generator.

Explainatio of the code :
* For the addition of even and odd index elements:
- Threads are organized into blocks to process segments of the array.
- Each thread calculates its index to access array elements.
- Memory management involves optimizing access patterns for reading array elements from global memory.
- Kernel functions are written to iterate through the array and sum even and odd indexed elements separately.
- Synchronization may be needed for shared resources or calculations.
- Atomic operations can prevent race conditions when updating shared variables.

Assignment 2. Implement Vector Matrix multiplication using column-wise decomposition method.

Explaination of the code :
*For vector-matrix multiplication using column-wise decomposition:
- Columns of the matrix are processed independently by different threads.
- Memory access patterns are optimized for efficient access to matrix and vector elements.
- Loops are optimized to efficiently iterate over matrix columns and perform vector multiplication.
- Data dependencies must be managed to ensure correct results.
- Performance tuning involves profiling and optimizing parameters like block size and memory access patterns.

Learnings :

State of the art computers are parallel computers, which comprise of multiple processors and provide a
platform to speed up computation in order to obtain faster results. Modern day computation tasks and
applications are becoming increasingly compute- and data-intensive.
