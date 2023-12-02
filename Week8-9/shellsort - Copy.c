/**************************************************************/
/*  shellsort.c--shell sort                                 */
/*This program sorts a list of n elements in ascending  order*/
/*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 10000
#define TRUE 1
#define FALSE 0

void shellsort(int x[], int n);

int main()
{
    int x[MAX_SIZE];              /*array to be sorted*/
    int num_items;                    /*num of items in list*/
    int i;                      /*loop counter         */
    double time_spent=0.0;      /*to calculate time for algorithm*/

    /*read in array to be sorted*/
    printf("\n Shell Sort");
     printf("\n Number of element in list to be sorted %d: ",MAX_SIZE);
    num_items=MAX_SIZE;
    for (i=0;i<num_items;++i)
    {
        printf("\n Enter  x(%d): ",i);
        x[i]=rand();
        printf("%d",x[i]);
    }
    /*activate shell sort and kick start the timing*/
    clock_t begin =clock();     /*start timimg*/
    shellsort(x,num_items);
    clock_t end = clock();      /*end timimg*/
    time_spent += (double)(end-begin)/CLOCKS_PER_SEC;
    /*print sorted list*/
    printf("\n The sorted list is ");
    for (i=0;i<=num_items-1;++i)
    {
        printf("\n%d",x[i]);
    }
    printf("\n Time in sorting %d value using shell sort algorithm is %f seconds\n",MAX_SIZE, time_spent);
    return 0;
}
/********************************************************/
/*  function : shell sort                              */
/*  sort an array in ascending order                    */
/*  Input :                                             */
/*    x[]-array to be sorted                            */
/*    n  - number of element in the array               */
/*   Return:                                           */
/*    x[]-sorted array                                  */
/*******************************************************/
void shellsort(int x[], int n)
{
    int i;        /*loop counter*/
    int temp;    /*temporary storage*/
    int last;       /*last eleemnt in unsorted list*/
    int is_sorted;   /*indicator to indicate if array is sorted*/
    int jump=n/2;    /*distance over which to compare*/

    while (jump>=1)
    {
        last=n-jump;
        is_sorted =FALSE;
        while (!is_sorted)
        {
            is_sorted=TRUE;     /*initialize flag*/
            for (i=0;i<last;++i)
            {
                if (x[i]>=x[i+jump])
                {
                    temp=x[i];
                    x[i]=x[i+jump];
                    x[i+jump]=temp;
                    is_sorted=FALSE;    /*reset flag*/
                }
             }
        }
        jump=jump/2;        /*redice interval distance*/
    }   
} 