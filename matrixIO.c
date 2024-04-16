#include<stdio.h>
#include"./include/matrix.h"
#include<stdlib.h>
#include<unistd.h>

void print_matrix(struct Matrix mat)
{
    for(int i=0;i<mat.row;i++)
    {
        for(int j=0;j<mat.col;j++)
        {
            printf("%.2f ",mat.data[i*mat.row + j]);
        }
        printf("\n");
    }
    printf("\n");
}

void write_matrix2file(const char * filename, struct Matrix mat)
{
    FILE * file = NULL;
    file = fopen(filename,"w"); 
    if (file == NULL) {fputs("File error", stderr); exit(1);}
    int row = mat.row;
    int col = mat.col;
    for(int i=0;i<row;i++)
    {
        for(int j=0;j<col;j++)
        {
            fprintf(file,"%6.2f ",mat.data[i*col+j]);
        }
        fprintf(file,"\n");
    }
    fclose(file);
}

struct Matrix read_matrix(struct Matrix mat)
{
    printf("the size of the matrix is:\n");
    scanf("%d %d",&mat.row,&mat.col);
    printf("please insert the elements of the matrix:\n");
    printf("%d %d \n",mat.row,mat.col);
    
    for(int i=0;i<mat.row;i++)
        for(int j=0;j<mat.col;j++)
        {
            scanf("%f",&mat.data[i*mat.row + j]);
        }
    return mat;
    
}

struct Matrix read_matrix_from_file(struct Matrix  mat, const char* dir)
{
    FILE * file = NULL;
    file = fopen(dir, "r");
    fscanf(file,"%d",&mat.row);
    fscanf(file,"%d",&mat.col);
       
    for(int i=0;i<mat.row;i++)
    {
        for(int j=0;j<mat.col;j++)
        {          
            fscanf(file,"%f",&mat.data[i*mat.row+j]);
        }
    }
    

    fclose(file);
    return mat;
}