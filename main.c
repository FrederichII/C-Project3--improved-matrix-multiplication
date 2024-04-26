#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include"./include/matrix.h"
#include"./include/matrixIO.h"
#include"./include/multiply.h"


#define _ADD(A, B) mat_add(A,B)
#define _NEG(A) mat_neg(A)
#define _WINO(A,B) Winograd_multiply_square(A,B)
#define _NAIVE(A,B) naive_multiply_square(A,B)

int main(int argc, char * argv)
{
    struct Matrix A;
    struct Matrix B;
    struct Matrix C;
    A = read_matrix_from_file(A,"./data/1000by1000/1.txt");
    B = read_matrix_from_file(B,"./data/1000by1000/2.txt");
    double time1, time2;
    clock_t start1, start2, end1, end2;
    start1 = clock();
    size_t test_times = 1;
    for (size_t i=0;i<test_times;i++)
    {
        C = naive_multiply_square(A, B);
    }
    end1 = clock();    
    write_matrix2file("./data/out_naive.txt", C);
    start2 = clock();
    for(size_t i=0;i<test_times;i++)
    {
        C = _WINO(A,B);
    }
    end2 = clock();
    time1 = (double)(end1 - start1) * 1000 / CLOCKS_PER_SEC / test_times;
    time2 = (double)(end2 - start2) * 1000 / CLOCKS_PER_SEC / test_times;
    write_matrix2file("./data/out_wino.txt", C);
    printf("time consumption of Naive MM is: %lf ms\n", time1);
    printf("time consumption of Winograd MM is: %lf ms\n", time2);
    free(C.data);
    free(A.data);
    free(B.data);
}   