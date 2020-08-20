# BSF-skeleton
The BSF-skeleton is designed for creating parallel programs in C++ using the MPI library. The scope of the BSF-skeleton is cluster computing systems and iterative numerical algorithms of high computational complexity. The BSF-skeleton completely encapsulates all aspects that are associated with parallelizing a program on a cluster computing system.
The theoretical basis of the BSF-skeleton is the BSF (Bulk Synchronous Farm) model of parallel computations, which allows predicting the scalability boundary  of a parallel algorithm/program at an early stage of its development. The scalability boundary is the maximum number of processor nodes that speedup increases to. A detailed description of the BSF parallel computation model can be found in the paper http://arxiv.org/abs/2008.03485.

This repository includes User manual that explains in detail how to quickly create correct and efficient parallel programs for computing clusters using the BSF skeleton.
