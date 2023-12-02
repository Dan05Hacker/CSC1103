#include <stdio.h>
#include "matrix.h"

void matrix_print(double x[][maxcol],int num_row,int num_col, int choice)
{
    int i,j;
    if (choice==0)
    {
        printf("\n______________________________________\n") ;
        printf("Following is the Matrix entered");
        printf("\n_______________________________________\n") ;
    }
    if (choice==1)
    {
        printf("\n________________________________________\n") ;
        printf("The addition of two matrix A and B is ");
        printf("\n_________________________________________\n") ;
    }
    if (choice==2)
    {
        printf("\n__________________________________________\n") ;
        printf("The subtraction of two matrix A and B is ");
        printf("\n___________________________________________\n") ;
    }
    if (choice==3)
    {
        printf("\n_____________________________________________\n") ;
        printf("The multiplication of two matrix A and B is ");
        printf("\n______________________________________________\n") ;
    }
    printf("\n");
    for (i=0;i<num_row;++i)
    {
        for (j=0;j<num_col;++j)
        {
            printf("%le  ",x[i][j]);
        }
        printf("\n");
    }
}