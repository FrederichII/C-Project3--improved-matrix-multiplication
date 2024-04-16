#include<stdio.h>
#include<math.h>
#include"./include/matrix.h"
#include"./include/multiply.h"
#include<stdlib.h>
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

struct Matrix naive_multiply(struct Matrix A, struct Matrix B)
{
    int rowA = A.row;
    int colA = A.col;
    int rowB = B.row;
    int colB = B.col;
    if(!(rowA==colA&&rowB==colB))
    {
        printf("Matrix not square\n");
        exit(EXIT_FAILURE);
    }
    if(!(rowA==rowB&&colA==colB))
    {
        printf("Dimensions not equal\n");
        exit(EXIT_FAILURE);
    }
    int m = rowA;
    struct Matrix C;
    C.row = rowA;
    C.col = colA;
    
    for(int i=0;i<sizeof(C.data)/sizeof(float);i++)
    {
        C.data[i] = 0;
    }

    for(int i=0;i<m;i++)
        for(int j=0;j<m;j++)
            for(int k=0;k<m;k++)
            {
                C.data[i*m + j] += A.data[i*m + k] * B.data[k*m + j];
            }

    return C;
}

struct Matrix mat_add(struct Matrix A, struct Matrix B)
{
    int rowA = A.row;
    int rowB = B.row;
    int colA = A.col;
    int colB = B.col;
    if(rowA!=rowB||colA!=colB)
    {
        printf("Matrices are not addable.");
        exit(EXIT_FAILURE);
    }
    struct Matrix C;
    C.col = A.col;
    C.row = A.row; 
    for(int i=0;i<sizeof(C.data)/sizeof(float);i++)
    {
        C.data[i] = 0;
    }
    for(int i=0;i<rowA;i++)
    {
        for(int j=0;j<colA;j++)
        {
            C.data[i*colA+j] = A.data[i*colA+j] + B.data[i*colA+j];
        }
    }
    return C;
}