#include<stdio.h>
#include"./include/matrix.h"
#include"./include/matrixIO.h"
#include"./include/multiply.h"

int main(int argc, char * argv)
{
    struct Matrix A;
    struct Matrix B;
    struct Matrix C;
    A = read_matrix_from_file(A,"./data/100by100/1.txt");
    B = read_matrix_from_file(B,"./data/100by100/2.txt");
    A = get_matrix_block(0,49,0,49,A);
    B = get_matrix_block(50,99,50,99,B);
    A = padding(A);
    B = padding(B);
    C = naive_multiply_square(A, B);
    write_matrix2file("./data/out.txt", A);
}    