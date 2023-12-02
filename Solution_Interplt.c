/************************************************************/
/*      Solution_interplt.c----Linear interpolation         */
/*      Computes the slope and intercept of a straight line */
/*      given the coordinates of the two points on the line */
/*      It also computes the y coordinates of a point given */
/*      the x coordinates                                   */
/************************************************************/

/*preprocessor statements  */
#include <stdio.h>

int main()
{
    float   x1,y1,x2,y2;             /*coordinates of two points on line        */
    float   m,c;                     /*slope and intercept of line              */
    float   x,y;                     /*coordinates of point to be interpolated  */

    printf("\n\t Linear Interpolation");

    /*input*/
    printf("\n\n Enter x and y coordinates of first point: ");
    scanf("%f %f", &x1, &y1);
    printf("\n\n Enter x and y coordinates of second point: ");
    scanf("%f %f", &x2, &y2);
    printf("\n\n Enter x coordinates to be interpolated: ");
    scanf("%f", &x);

     /*computation*/
     m=(y2-y1)/(x2-x1);         /* slope or gradient of line        */
     c=(y1*x2-y2*x1)/(x2-x1);   /*y intercept                       */
     y=m*x+c;

    /*print result*/
     printf("\n\n slope or gradident of the line =%f",m);
     printf("\n y-intercept of line =%f",c);
     printf("\n Y coordinates of point =%f\n",y);
}

