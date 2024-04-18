#include<stdio.h>
#include<math.h>
#include"./include/matrix.h"
#include"./include/multiply.h"
#include"./include/matrixIO.h"
#include<stdlib.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define _ADD(A, B) mat_add(A,B)
#define _NEG(A) mat_neg(A)
#define _WINO(A,B) Winograd_multiply_square(A,B)
#define _NAIVE(A,B) naive_multiply_square(A,B)

struct Matrix naive_multiply_square(struct Matrix A, struct Matrix B)
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
    C.data = malloc(C.row*C.col*sizeof(float));

    for(int i=0;i<C.row*C.col;i++)
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
        printf("Matrices are not addable.\n");
        exit(EXIT_FAILURE);
    }
    struct Matrix C;
    C.col = A.col;
    C.row = A.row; 
    C.data = malloc(C.row*C.col*sizeof(float));
    for(int i=0;i<C.row*C.col;i++)
    {
        C.data[i] = 0;
    }
    for(int i=0;i<rowA;i++)
    {
        for(int j=0;j<colA;j++)
        {
            C.data[i*colA + j] = A.data[i*colA+j] + B.data[i*colA+j];
        }
    }
    return C;
}

struct Matrix mat_neg(struct Matrix mat)
{
    for(int i=0;i<mat.row;i++)
    {
        for(int j=0;j<mat.col;j++)
        {
            mat.data[i*mat.col + j] *= -1;
        }
    }
    return mat;
}

// get the sub-matrix slice [x0:x1][y0:y1] of Matrix "mat".
struct Matrix get_matrix_block(int x0, int x1, int y0, int y1, struct Matrix mat)
{
    struct Matrix block;
    block.row = x1-x0+1;
    block.col = y1-y0+1;
    block.data = malloc(block.row*block.col*sizeof(float));
    int i=0;
    for(int m=x0;m<=x1;m++)
    {
        int j=0;
        for(int n=y0;n<=y1;n++)
        {
            block.data[i*block.col + j] = mat.data[m*mat.col + n];
            j++;
        }
        i++;
    }
    return block;
}

struct Matrix padding(struct Matrix mat)
{
    struct Matrix padded;
    int row = mat.row;
    int col = mat.col;
    padded.row = row+1;
    padded.col = col+1;
    padded.data = malloc(padded.row*padded.col*sizeof(float));
    int cursor = 0;
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            padded.data[cursor] = mat.data[i*col+ j];
            cursor ++;
        }
        padded.data[cursor] = 0;
        cursor ++;
    }
    cursor ++;
    for(int i=0;i<padded.col;i++)
    {
        padded.data[cursor] = 0;
    }
    return padded;
}

struct Matrix mat_assemble(struct Matrix C11, struct Matrix C12, struct Matrix C21, struct Matrix C22)
{
    if(C11.row!=C12.row || C11.col != C21.col || C21.row!=C22.row || C12.col!=C22.col)
    {
        printf("assemble failed, please check the size of the blocks.\n");
        exit(EXIT_FAILURE);
    }
    struct Matrix C;
    C.row = C11.row + C21.row;
    C.col = C11.col + C12.col;
    C.data = malloc(C.row*C.col*sizeof(float));
    for(int i=0;i<C.row;i++)
    {
        for(int j=0;j<C.col;j++)
        {
            float tmp1 = (i<C11.row?C11.data[i*C11.col + j]:C21.data[(i-C11.row)*C21.col + j]);
            float tmp2 = (i<C11.row?C12.data[i*C12.col + (j-C11.col)]:C22.data[(i-C11.row)*C22.col + (j-C11.col)]);
            C.data[i*C.col + j] = (j<C11.col?tmp1:tmp2);
        }
    }
    return C;
}

struct Matrix Winograd_multiply_square(struct Matrix A, struct Matrix B)
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
    // recursion cut-off condition: m<=12
    if(m <= 12)
    {
        return _NAIVE(A, B);
    }
    _Bool odd = 0;
    if(m%2 == 1)
    {
        odd = 1;
        A = padding(A);
        B = padding(B);
    }
    m = A.row; // to update the value of m(padding changes the value of m)
    // matrix blocks
    struct Matrix A11, A12, A21, A22;
    struct Matrix B11, B12, B21, B22;
    // intermediate variables
    struct Matrix S1, S2, S3, S4, T1, T2, T3, T4;
    struct Matrix P1, P2, P3, P4, P5, P6, P7;
    struct Matrix U1, U2, U3, U4, U5, U6, U7;
    // result matrix
    struct Matrix C;
    printf("%d ",m);
    // stage(1): get matrix blocks
    A11 = get_matrix_block(0, m/2-1, 0, m/2-1, A);
    A12 = get_matrix_block(0, m/2-1, m/2, m-1, A);
    A21 = get_matrix_block(m/2, m-1, 0, m/2-1, A);
    A22 = get_matrix_block(m/2, m-1, m/2, m-1, A);
    
    B11 = get_matrix_block(0, m/2-1, 0, m/2-1, B);
    B12 = get_matrix_block(0, m/2-1, m/2, m-1, B);
    B21 = get_matrix_block(m/2, m-1, 0, m/2-1, B);
    B22 = get_matrix_block(m/2, m-1, m/2, m-1, B);

    
    // stage (2): compute linear combination of matrix blocks
    S1 = _ADD(A21,A22);
    S2 = _ADD(S1,_NEG(A11));
    S3 = _ADD(A11,_NEG(A21));
    S4 = _ADD(A12,_NEG(S2));

    T1 = _ADD(B12,_NEG(B11));
    T2 = _ADD(B22,_NEG(T1));
    T3 = _ADD(B22,_NEG(B12));
    T4 = _ADD(B21,_NEG(T2));
    // stage (3): compute the product of the combinations, which is recursive
    
    P1 = _WINO(A11,B11);
    P2 = _WINO(A12,B21);
    P3 = _WINO(S1,T1);
    P4 = _WINO(S2,T2);
    P5 = _WINO(S3,T3);
    P6 = _WINO(S4,B22);
    P7 = _WINO(A22,T4);
    // stage (4): add the products
    U1 = _ADD(P1,P2); // C11
    U2 = _ADD(P1,P4); 
    U3 = _ADD(U2,P5);
    U4 = _ADD(U3,P7); // C21
    U5 = _ADD(U3,P3); // C22
    U6 = _ADD(U2,P3);
    U7 = _ADD(U6,P6); // C12
    C = mat_assemble(U1,U7,U4,U5);
    
    if(odd == 1)
    {
        C = get_matrix_block(0,C.row-2,0,C.col-2,C);
    }
    
    
    return C;
}