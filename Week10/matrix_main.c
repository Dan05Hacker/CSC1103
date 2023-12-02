#include "matrix.h"

int main()
{
    int choice=0;
    matrix_read(A,&num_row,&num_col);
    matrix_print(A,num_row,num_col,choice);
    matrix_read(B,&num_row,&num_col);
    matrix_print(B,num_row,num_col,choice);
    choice=1; 
    matrix_ops(A,B,C,num_row,num_col,choice);
    matrix_print(C,num_row,num_col,choice);
    choice=2;
    matrix_ops(A,B,C,num_row,num_col,choice);
    matrix_print(C,num_row,num_col,choice);
    choice=3;
    matrix_ops(A,B,C,num_row,num_col,choice);
    matrix_print(C,num_row,num_col,choice);
}