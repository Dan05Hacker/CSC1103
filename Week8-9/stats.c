/****************************************************/
/* stats.c      -sample statistics                  */
/*                                                  */
/*  computes the statistics for a group of data     */
/*  It computes the mean, variance,min/max of data  */
/****************************************************/

#include <stdio.h>
#include <math.h>

#define MAX_SIZE    50
#define FALSE       0
#define TRUE        1

void stats(float x[], int N,float *p_min,float *p_max,float *p_mean,float *p_var);
void shellsort(float x[],int n);
int main()
{
    float x[MAX_SIZE];
    float xmin, xmax,mean, var;
    int N,i;

    /*get input*/
    printf("\n SAMPLE STATISTICS \n");
    printf(" Enter number of items: ");
    scanf("%d", &N);
    for (i=0;i<N;++i)
    {
        printf("Enter value for x(%d):",i);
        scanf("%f",&x[i]);
    }
    /*call function to compute the statistics*/
    stats(x,N,&xmin, &xmax,&mean,&var);
    /*print results*/
    printf("\n SAMPLE STATISTICS\n");
    printf("\n Sample Size=%d\n",N);
    printf("\n Minimum value =%f\n",xmin);
    printf("\n Maximum=%f\n",xmax);
    printf("\n Mean value =%f\n",mean);
    printf("\n Var value =%f\n",var);
}
/****************************************************/
/* function:stats()                                 */
/*                                                  */
/*  computes the statistics for a group of data     */
/*  Input parameters:                               */
/*  x[]    -array containing data items             */
/*   N     -sample size                             */
/*  Output parameters:                              */
/*  *mean  -mean value                              */
/*  *var   -variance value                          */
/*  *min   -minimum value                           */
/*  *max   -maximum value                           */
/****************************************************/
void stats(float *x, int N, float *p_min, float *p_max,float *p_mean,float *p_var)
{
    int i;
    float sumx, sumxx;      /*sum of x and x^2*/

    *p_min=x[0];            /*initialize min value pointed by p_min to first value of x*/            
    *p_max=x[0];            /*initialize max value pointed by p_max to first value of x*/

    shellsort(x,N);
    /*minimum and maximum value*/
    *p_min=x[0];
    *p_max=x[N-1];
    /*compute mean, variance, variance*/
    sumx=x[0];              /*initialize sumx to first value of x*/
    sumxx=x[0]*x[0];        /*initialize sumx to first value of x*/
    for(i=1;i<N;++i)
    {
        sumx +=x[i]; 
        sumxx +=x[i]*x[i];
    }
    *p_mean=sumx/N;
    *p_var=(sumxx-N*(*p_mean**p_mean))/(N-1);
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
void shellsort(float x[], int n)
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