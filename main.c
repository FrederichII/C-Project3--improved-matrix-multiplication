#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include <sys/time.h>
#include"./include/matrix.h"
#include"./include/matrixIO.h"
#include"./include/multiply.h"



#define _ADD(A, B) mat_add(A,B)
#define _NEG(A) mat_neg(A)
#define _WINO(A,B) Winograd_multiply_square(A,B)
#define _NAIVE(A,B) naive_multiply_square(A,B)

long long get_wall_time() {
    struct timeval time;
    gettimeofday(&time, NULL);
    return (long long)time.tv_sec * 1000000 + (long long)time.tv_usec;
}

int main(int argc, char * argv)
{
    long long big_start, big_end;
    big_start = get_wall_time();
    
    struct Matrix A;
    struct Matrix B;
    struct Matrix C;
    A = read_matrix_from_file(A,"./data/3000by3000/1.txt");
    B = read_matrix_from_file(B,"./data/3000by3000/2.txt");
    double time1, time2;
    
    long long start_wall1, start_wall2, end_wall1, end_wall2;
    clock_t start1, start2, end1, end2;
    start1 = clock();
    start_wall1 = get_wall_time();
    size_t test_times = 1;
    for (size_t i=0;i<test_times;i++)
    {
        C = naive_multiply_square(A, B);
    }
    end_wall1 = get_wall_time();
    end1 = clock();       
    write_matrix2file("./data/out_naive.txt", C);
    start2 = clock();
    start_wall2 = get_wall_time();
    for(size_t i=0;i<test_times;i++)
    {
        C = _WINO(A,B);
    }
    end2 = clock();  
    end_wall2 = get_wall_time();
    write_matrix2file("./data/out_wino.txt", C);

    double walltime1 = (double)(end_wall1 - start_wall1) / 1000.0; 
    double walltime2 = (double)(end_wall2 - start_wall2) / 1000.0; 
    time1 = (double)(end1 - start1) * 1000 / CLOCKS_PER_SEC / test_times;
    time2 = (double)(end2 - start2) * 1000 / CLOCKS_PER_SEC / test_times;
    big_end = get_wall_time();
    printf("time consumption of Naive MM is: %lf ms\n", time1);
    printf("time consumption of Winograd MM is: %lf ms\n", time2);
    printf("wall time of Naive MM is %lf ms\n", walltime1);
    printf("wall time of Winograd MM is %lf ms\n", walltime2);
    double big_wall_time =  (double)(big_end - big_start) / 1000.0;
    printf("overall wall time is %lf ms\n", big_wall_time);
    free(C.data);
    free(A.data);
    free(B.data);
    
}   