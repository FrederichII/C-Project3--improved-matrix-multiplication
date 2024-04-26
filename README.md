# C-Project3--improved-matrix-multiplication

2024 Spring SUStech CS205 C/C++ Programming: Project3--improved matrix multiplication

​	我使用了Coppersmith - Winograd的基于分治思想的矩阵乘法算法，我的实验证明了此算法比三重循环的朴素矩阵乘法算法快上不少，且能得到正确的结果，在矩阵大小为3000时，此算法的CPU time大约在8秒左右，而三重循环的算法的CPU time则约为120秒左右。目前，这些都是在没有使用avx2和openmp进行并行化加速的条件下，我想如果能使用avx2和openmp进行进一步加速，该算法的优势能被更好地发挥出来，然而，在进行并行化的过程中遇到了非常多的问题，我尝试了包括GDB在内的各种调试办法，到现在也没办法解决：

* 并行化后Winograd算法和Naive算法的结果不一致（但数量级基本正确），且结果不正确

* 并行化后的耗时总是大于并行化之前的耗时，并且可以排除不是由于矩阵太小导致并行化的优势发挥不出来（测试集都使用1000x1000以上的矩阵）

* 并行化后很容易报segmentation fault，根据GDB的提示，似乎问题在于malloc的使用上，但我无法排查出来

  
