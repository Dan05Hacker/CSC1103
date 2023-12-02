#include <stdio.h>
#include <math.h>
/*************************/
/*          AND Operation*/
/*          x1     x2   y*/
/* case1:    0      0   1*/
/* case2:    0      1   0*/
/* case3:    1      0   0*/
/* case4:    1      1   0*/
/****************/

/*Global Variable*/
float alpha=0.5;
float w1=0;        /*weight for x1*/
float w2=0;        /*weight for x2*/
float b=0;              /*bias*/
float errortol=0;       /*prediction error tolerance*/
int x1=0, x2=0, y=0;    /*input training data and ouput*/
float errory=0;
float errorx1=0;
float errorx2=0;

void estimationerror(int x1, int x2, int y);
void parameterupdate(int iter);
void selectdata(int row);

int main()
{
    int iter=1;
    int row=1;
    /*training phase with training data*/
    do
    {
        errory=0;
        errorx1=0;
        errorx2=0;
        for(row=1;row<5;row++)
        {   
            /*select training data */
            selectdata(row);
            estimationerror(x1,x2,y);         /*training input to estimate the error based on the weight and bias*/          
        }
        parameterupdate(iter);          /*update the weight and bias*/
        iter++;
    }
    while (fabs(errory)>errortol);
    printf("\nTotal training iteration is %d with totalerror is %f ", iter-1,errory);
    printf("\nFinal trained weight_1, trained weight_2, training bias b is %f, %f ,%f ", w1,w2, b);
    /*testing phase with tested data*/
    printf("\n\nPls enter the tested data x1 :");
    scanf("%d",&x1);
    printf("\nPls enter the tested data: x2 : ");
    scanf("%d",&x2);
    printf("\nPredicted output y : %f", w1*x1+w2*x2+b);
    return 0;
}

void selectdata(int row)
{
     if (row==1 )/* case 1 */
            {
                x1=0;
                x2=0;
                y=0;
            }
            if (row==2 )/* case 2 */
            {
                x1=0;
                x2=1;
                y=0;
            }
            if (row==3 )/* case 3 */
            {
                x1=1;
                x2=0;
                y=0;
            }
            if (row==4 )/* case 4 */
            {
                x1=1;
                x2=1;
                y=1;
            }
}

void estimationerror(int x1, int x2, int y)
{
     float yest=0;         /*estimation of output y*/

     yest=w1*x1+w2*x2+b;     /*linear regression to estimate output y*/
    yest=yest>0?1:0;
     errory+=(yest-y);
     errorx1+=(yest-y)*x1;
     errorx2+=(yest-y)*x2;
}

void parameterupdate(int iter)
{
        printf("\nAt iteration %d, error is %f ", iter,errory);
        printf("\nOld w1=%f",w1);
        printf("\nold w2=%f",w2);
        printf("\nold b=%f",b);
        w1-=(alpha*errorx1);/*update weight1*/
        w2-=(alpha*errorx2);/*update weight2*/
        b-=(alpha*errory);      /*update bias b*/
        printf("\nnew w1=%f",w1);
        printf("\nnew w2=%f",w2);
        printf("\nnew b=%f",b);
}
