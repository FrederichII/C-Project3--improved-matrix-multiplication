# C-Project3--improved-matrix-multiplication
2024 Spring SUStech CS205 C/C++ Programming: Project3--improved matrix multiplication

#### branch: developing
This branch changed the data representation of Matrix from a fixed-length float array to a float pointer, where the memory allocation is done when a Matrix variable is declared and initialized. This can fix the problem that Matrix of size over 100 x 100 results in segmentation fault, and can calculate matrix multiplication by Winograd algorithm of matrix of size up to 1000 x 1000. However, new problem arises: the result by Winograd is no longer consistent with the Naive result, which is still being fixed.