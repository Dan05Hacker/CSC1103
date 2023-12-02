/**************************************************************/
/*  selsort.c--selection sort                                 */
/*This program sorts a list of n elements in ascending  order*/
/*************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 10000
void selection(int x[], int n);

int main()
{
    int x[MAX_SIZE];              /*array to be sorted*/
    int num_items;                    /*num of items in list*/
    int i;                      /*loop counter         */
    double time_spent=0.0;      /*to calculate time for algorithm*/

    /*read in array to be sorted*/
    printf("\n Selection Sort");
    printf("\n Number of element in list to be sorted %d: ",MAX_SIZE);
    num_items=MAX_SIZE;
    for (i=0;i<num_items;++i)
    {
        printf("\n Enter  x(%d): ",i);
        x[i]=rand();
        printf("%d",x[i]);
    }
    /*activate selection sort and kick start the timing*/
    clock_t begin =clock();     /*start timimg*/
    selection(x,num_items);
    clock_t end = clock();      /*end timimg*/
    time_spent += (double)(end-begin)/CLOCKS_PER_SEC;
    /*print sorted list*/
    printf("\n The sorted list is ");
    for (i=0;i<=num_items-1;++i)
    {
        printf("\n%d",x[i]);
    }
    printf("\n Time in sorting %d value using selection sort algorithm is %f seconds\n",MAX_SIZE, time_spent);
    return 0;
}
/********************************************************/
/*  function : selection sort                           */
/*  sort an array in ascending order                    */
/*  Input :                                             */
/*    x[]-array to be sorted                            */
/*    n  - number of element in the array               */
/*   Return:                                           */
/*    x[]-sorted array                                  */
/*******************************************************/
void selection(int x[], int n)
{
    int pass;
    int i=0;
    int imin;
    int min;
    int temp;

    for (pass=0;pass<n-1;++pass)
    {
        min=x[pass];
        imin=i;

        for (i=pass+1;i<n;++i)
        {
            if (x[i]<min)
            {
                min=x[i];
                imin=i;
            }
        }
        temp=x[pass];
        x[pass]=min;
        x[imin]=temp;

        
    }
} 