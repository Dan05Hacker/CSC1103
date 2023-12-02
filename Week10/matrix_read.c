#include <stdio.h>
#include "matrix.h"

void matrix_read(double x[][maxcol], int *ptr_row, int *ptr_col)
{
    int i,j;
    /*get number of rows and columns*/
    printf("\n number of rows in matrix: ");
    scanf("%d",ptr_row);
    printf("\n number of column in matrix: ");
    scanf("%d",ptr_col);
    printf("\n Enter elements at a time");
    for (i=0;i<*ptr_row;++i)
    {
        for (j=0;j<*ptr_col;++j)
        {
            printf("\n Element %d %d = ",i+1,j+1);
            scanf("%lf",&x[i][j]);                      
        }
    }
}