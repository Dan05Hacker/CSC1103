/****************************************************/
/*Binom.c-------Evaluate (x+y) raised to the power n*/
/* This program will evaluate (x+n) raised to power n*/
/*using a series expanison. Both x and y are of type*/
/*double and n is of type int                       */
/****************************************************/
#include <stdio.h>
#include <stdlib.h>

double x_plus_y (double x, double y, int n);
double binom(int n, int k);
double power (double x, int n);
int factorial (int m);

int main ()
{
    double x,y,result;
    int n;
    /*read input*/
    printf("\nPlease input the value of x :");
    scanf("%lf",&x);
    printf("\nPlease input the value of y :");
    scanf("%lf",&y);
    printf("\nPlease input the value of n :");
    scanf("%d",&n);
    /*call x_plus_y function*/
    result=x_plus_y(x,y,n);
    printf("\n (%lf + %lf) raised to the power %d is %lf\n",x,y,n,result);
    return 0;
}

/****************************************************************/
/*function :x_plus_y                                            */
/*Evaluates (x+y) raised to the power n using a series expansion*/
/*                                                              */
/*input Parameters:                                             */
/*  x- number (double)                                          */
/*  y-number (double)                                           */
/*  n-integer exponent (int)                                    */
/*                                                              */
/* output Parameter                                             */
/*  none                                                        */
/*                                                              */
/*  returns:                                                    */
/*  (x+y)raised to the power of n as a double value             */
/****************************************************************/
double x_plus_y(double x, double y, int n)
{
    int k;
    double sum=0.0;

    for (k=0;k<=n;k++)
    {
        sum +=binom(n,k)*power(x,n-k)*power(y,k);
    }
    return(sum);
}

/****************************************************************/
/*function :binom                                               */
/*compute the binmomial cofficient                              */
/*                                                              */
/*input Parameters:                                             */
/*  n (int)                                                     */
/*  k (int)                                                     */
/*                                                              */
/*                                                              */
/* output Parameter                                             */
/*  none                                                        */
/*                                                              */
/*  returns:                                                    */
/*  The binomial cofficient B(n,k) as double value              */
/****************************************************************/
double binom(int n, int k)
{
    int n_fact,k_fact,n_minus_k_fact;
    double result=1.0;

    n_fact=factorial(n);
    k_fact=factorial(k);
    n_minus_k_fact=factorial(n-k);
    result= n_fact/(k_fact*n_minus_k_fact);
    return(result);
}

/****************************************************************/
/*function :factorial                                           */
/*compute the factorial using recursive function                */  
/*                                                              */
/*input Parameters:                                             */
/*  m (int)                                                     */
/*                                                              */
/*                                                              */
/* output Parameter                                             */
/*  none                                                        */
/*                                                              */
/*  returns:                                                    */
/*  factorial (m)                                               */
/****************************************************************/
int factorial(int m)
{
    if (m==0)
        return (1);
    else
        return(m*factorial(m-1));
}
/****************************************************************/
/*function :power                                               */
/*compute x raised to the power n                               */  
/*                                                              */
/*input Parameters:                                             */
/*  x   -number                                                 */
/*  n   -integer exponent                                       */
/*                                                              */
/* output Parameter                                             */
/*  none                                                        */
/*                                                              */
/*  returns:                                                    */
/*  x raised to the power n (double)                            */
/****************************************************************/
double power (double x, int n)
{
    int i;
    double result =1.0;

    if (n==0)
        return(result);
    for (i=1;i<=abs(n);++i)
        result *=x;
    if (n>0)
        return (result);
    else
        return (1.0/result);
}