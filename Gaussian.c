#include <stdio.h>
#include <math.h>

#define PI 3.141592

int main()
{
    float delta,sigma,mu,x,xmin,xmax;
    double fx,sum;
  

    mu=1;               /*mean of the random normal variable x */
    sigma=2;            /*standard devaition of the random normal variable x */
    delta=0.5;          /* step size of the random normal variable x */
    xmin=-20;              /*starting minimum value of random normal variable x */    
    xmax=20;            /*maximum value of random normal variable x */       
    sum=0;             
    printf("\n Normal Distribution of a random variable x ranging from -20 to 20 ");
    printf("\n *********************************************************************");
    printf("\n Value of x           Value of f(x)");
    printf("\n __________________________________");
    x=xmin;
    while (x<=xmax)
    {
        fx=1/(sqrt(2*PI)*sigma)*exp(-0.5*pow((x-mu),2)/pow(sigma,2));
        printf("\n %f                   %e",x,fx);
        x+=delta;
        sum+=(fx*delta);
    }
    printf("\n sum=%e\n",sum);
    return 0;


}