/*****************************************************/
/* crossproduct.c---------cross product              */
/*                                                   */
/*  This program computes the cross product vector C */
/*  of two 3D vector A and B                         */
/*****************************************************/

#include <stdio.h>

void crossproduct(float a[3], float b[3], float c[3]);

int main ()
{
    float a[3], b[3], c[3];
    int i;

/********************************************************/
/*prompt for user input of Ax,Ay,Az and Bx,By, Bz       */
/********************************************************/
    printf("\nEnter the x,y,z component of vector A : ");
    for (i=0;i<=2;++i)
    {
       printf("\nEnter the a[%d] of vector A : ",i+1);
       scanf("%f",&a[i]);     
    }
    printf("\nEnter the x,y,z component of vector B : ");
    for (i=0;i<=2;++i)
    {
       printf("\nEnter the b[%d] of vector B : ",i+1);
       scanf("%f",&b[i]);     
    }
    /*********************************************************/
    /* call function crossproduct to return vector C         */
    /*********************************************************/
    crossproduct(a,b,c);
    /*********************************************************/
    /* print the vector c                                    */
    /********************************************************/
    printf("\nThe cross product vector C of two vector A and B is : ");
    for (i=0;i<=2;++i)
    {
       printf("\n c[%d] of vector C is %f: \n",i+1,c[i]);
    }
}
/***************************************************************/
/*  function:crossproduct                                      */
/*                                                             */
/*  Purpose:                                                   */
/*          This functions computes the cross product vector C */
/*          of two 3D vector A and B                           */
/*                                                            */
/*  Input   Paramters:                                        */
/*  a[]     -3D vector A with a[0]=Ax,a[1]=Ay,a[2]=Az         */
/*  b[]     -3D vector B with b[0]=Bx,b[1]=By,b[2]=Bz         */
/*  c[]     -empty 3D vector C with c[0]=Cx,c[1]=Cy,c[2]=Cz   */
/*************************************************************/

void crossproduct(float a[3], float b[3],float c[3])
{
    c[0]=a[1]*b[2]-a[2]*b[1];
    c[1]=a[2]*b[0]-a[0]*b[2];
    c[2]=a[0]*b[1]-a[1]*b[0];    
}