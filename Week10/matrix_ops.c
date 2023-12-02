#include "matrix.h"

void matrix_ops(double A[][maxcol],double B[][maxcol],double C[][maxcol],int num_row,int num_col,int choice)
{
    int i,j,k,p;

    p=num_col;
    switch(choice)
    {
     case 1:
        for (i=0;i<num_row;++i)
        {
            for (j=0;j<num_col;++j)
            {
                C[i][j]=A[i][j]+B[i][j];
            }
        }
        break;
    case 2:
        for (i=0;i<num_row;++i)
        {
            for (j=0;j<num_col;++j)
            {
                C[i][j]=A[i][j]-B[i][j];
            }
        }
        break;
    case 3:
        for (i=0;i<num_row;++i)
        {
            for (j=0;j<num_col;++j)
            {
                C[i][j]=0.0;
                for(k=0;k<p;++k)
                {
                    C[i][j]=C[i][j]+A[i][k]*B[k][j];
                }
                
            }
        }
        break;
    }
}