#include<stdio.h>
#include"./include/matrix.h"
#include"./include/matrixIO.h"
#include"./include/multiply.h"
#include<stdlib.h>

#define _ADD(A, B) mat_add(A,B)
#define _NEG(A) mat_neg(A)
#define _WINO(A,B) Winograd_multiply_square(A,B)
#define _NAIVE(A,B) naive_multiply_square(A,B)

int main(int argc, char * argv)
{
    struct Matrix A;
    struct Matrix B;
    struct Matrix C;
    A = read_matrix_from_file(A,"./data/small/1.txt");
    B = read_matrix_from_file(B,"./data/small/2.txt");
    A = get_matrix_block(0,48,0,48,A);
    B = get_matrix_block(0,48,0,48,B);
    //A = padding(A);
    //B = padding(B);
    C = naive_multiply_square(A, B);    
    write_matrix2file("./data/out_naive.txt", C);
    C = _WINO(A,B);
    write_matrix2file("./data/out_wino.txt", C);
    free(C.data);
    free(A.data);
    free(B.data);
}    