/**************************************************/
/*  quicksort.c---------quick sort                */
/*                                                */
/*  This program sorts an array using the quick   */
/*  alogorithm                                    */
/**************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 10000


void quick_sort(int x[], int first, int last);
int partition (int x[],int first, int last);

int main()
{
    int x[MAX_SIZE];         /* array to be sorted */
    int num_items;              /* number of elements in array*/
    int i;                      /* loop counter*/
    double time_spent=0.0;      /*to calculate time for algorithm*/

    /*read in array*/
    printf("\n Quick Sort ");
    printf("\n Number of element in list to be sorted %d: ",MAX_SIZE);
    num_items=MAX_SIZE;
    for (i=0;i<num_items;++i)
    {
        printf("\n Enter  x(%d): ",i);
        x[i]=rand();
        printf("%d",x[i]);
    }
    /* call quick sort function and kick start the timing*/
    clock_t begin =clock();     /*start timimg*/
    quick_sort(x,0,num_items-1);
    clock_t end = clock();      /*end timimg*/
    time_spent += (double)(end-begin)/CLOCKS_PER_SEC;
    /*print sorted array*/
    printf("\n\n sorted array \n");
    for (i=0;i<num_items;++i)
    {
        printf("\n%d ",x[i]);
    }
   printf("\n Time in sorting %d value using quicksort algorithm is %f seconds\n",MAX_SIZE, time_spent);
    return 0;
}

/*************************************************************/
/*  function:quick_sort                                      */
/*                                                           */
/*  Purpose:                                                 */
/*          This functions sorts an array in ascending  order*/
/*          using quicksort algorithm with recursive function*/
/*                                                           */
/*  Input   Paramters:                                       */
/*  x[]     -array to be sorted                              */
/*  first   -position of first element in the list           */
/*  last  -position of last element in the list              */
/*************************************************************/
void quick_sort(int x[], int first, int last)
{
    int pivot;              /*pivot element*/
    if(first<last)
    {
        pivot=partition(x,first,last);
        quick_sort(x,first,pivot-1);
        quick_sort(x,pivot+1,last);
    }
}

/**************************************************************/
/*  function:partition                                        */
/*                                                            */
/*  Purpose:                                                  */
/*          This functions partitions an array into two parts */
/*          based on the value of a pivot element. All element*/
/*          that are smaller than the pivot element are placed*/
/*          on the left.All elements that are bigger than the */
/*          pivot element are placedon the right. The pivot is*/
/*          taken to be the first element in the list         */
/*  Input   Paramters:                                        */
/*  x[]     -array to be sorted                               */
/*  first   -position of first element in the list            */
/*  last    -position of last element in the list             */
/*  Returns                                                   */
/*  pivot   -position of the pivot element                    */
/**************************************************************/
int partition(int x[], int first, int last)
{
    int pivot;              /*position of the pivot element*/
    int  pivot_value;    /*value of pivot element       */
    int temp;            /*temporary storage            */
    int i;
    pivot=first;
    pivot_value=x[first];
    for(i=first;i<=last;++i)
    {
        /*compare element with pivot element    */
        if (x[i]<pivot_value)
        {
            ++pivot;                    /*adjust index of pivot element*/
            if (i !=pivot)
            {
                /*interchange element with pivot element */
                temp=x[pivot];
                x[pivot]=x[i];
                x[i]=temp;
            }
        }
     
    }
    /* move pivot element to point in list that separate the    */
    /* smaller elements from the larger elements                */
    temp=x[pivot];
    x[pivot]=x[first];
    x[first]=temp;

    return (pivot);
}