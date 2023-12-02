#include <stdio.h>

int main()
{
    float m1,c1,xo,yo,m2,c2,m3,c3;
    /* Input Parameter for original line gradient m1 and y-intercept c1*/
    /* Input Parameter for x and y coordinate of point P*/
    printf("\nEnter the gradient of the original line : ");
    scanf("%f",&m1);
    printf("\nEnter the y intercept of the original line : ");
    scanf("%f",&c1);
    printf("\nEnter the x coordinate of the Point P : ");
    scanf("%f",&xo);
    printf("\nEnter the y coordinate of the Point P : ");
    scanf("%f",&yo);
    /*Calculate the gradient m2 and y intercept c2 of parallel line*/
    /*parallel line will have same gradient as orginal line*/
    m2=m1;   
    /*calculate y intercept at point x0 and y0*/       
    c2=yo-m2*xo;              
    /*Calculate the gradient m3 and y intercept c3 of perpendicular line*/
    /*perpendicular line will have gradient inverse negative of original line*/      
    m3=-1/m1;       
    /*calculate y intercept at point x0 and y0*/    
    c3=yo-m3*xo;
    /*print the equation of the original line, parallel line and perpendicular line*/
    printf("\nThe equation of the orginal line is y = %fx + %f",m1,c1);
    printf("\nThe equation of the parallel line is y = %fx + %f",m2,c2);
    printf("\nThe equation of the perpendicular line is y = %fx + %f\n",m3,c3);
    printf("\nThe x and y coordinates of point P is %f ,%f\n",xo,yo);
    return 0;
}