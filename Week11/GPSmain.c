#include <stdio.h>
#include <math.h>
#define maxsize 3                       /*define the size: Actual size is 10,000;Put 3 for demo*/

struct point_3D {/*total 12 bytes*/
                float x; /*4 bytes*/
                float y;/*4 bytes*/
                float z;/*4 bytes*/
                };
struct Euc_dist2D{/*Eculidean Distance = comprises of Pythagorean theorem in multiple dimension*//*48bytes */
                struct point_3D GPScoord[maxsize];
                float distance2D[maxsize-1];
                float total_distance;
                };
struct Euc_dist3D{/*36+8+4=48 bytes*/
                struct point_3D GPScoord[maxsize];/*3x12=36 if maxsize=3*/
                float distance3D[maxsize-1];/*2x4=8 if maxsize=3*/
                float total_distance;/*4 bytes*/
                };
union Euc_dist{
                struct Euc_dist2D dist_travel2D;
                struct Euc_dist3D dist_travel3D;
                };

void read_points(union Euc_dist *ptr_dist_travel,int);       
void dist_cal(union Euc_dist *ptr_dist_travel,int);
void print_dist(union Euc_dist *ptr_dist_travel,int);

int main()
{       

        union Euc_dist dist_travel, *ptr_dist_travel;
        int choice;

        ptr_dist_travel=&dist_travel;
        printf("\nPls enter the choice 1)2D Distance calculation");
        printf("\n                     2)3D Distance calculation");
        printf("\nChoice : ");
        scanf("%d",&choice);
        read_points(ptr_dist_travel,choice);
        dist_cal(ptr_dist_travel,choice);
        print_dist(ptr_dist_travel,choice);
        printf("\n Memory required for the Union variable is %lu",sizeof (dist_travel));
}

void read_points(union Euc_dist *ptr_dist_travel,int choice)
{
        int i;
        switch(choice)
        {
                case 1:
                {
                        for (i=0;i<maxsize;++i)  
                        {
                                printf("\nPls enter the x coordinate of point %d :",i+1);
                                scanf("%f",&(ptr_dist_travel->dist_travel2D.GPScoord[i].x));
                                printf("\nPls enter the y coordinate of point %d ",i+1);
                                scanf("%f",&(ptr_dist_travel->dist_travel2D.GPScoord[i].y));
                                printf("\nPls enter the z coordinate of point %d ",i+1);
                                scanf("%f",&(ptr_dist_travel->dist_travel2D.GPScoord[i].z));
                        }   
                        break;  
                }
                case 2:
                {
                        for (i=0;i<maxsize;++i)  
                        {
                                printf("\nPls enter the x coordinate of point %d :",i+1);
                                scanf("%f",&(ptr_dist_travel->dist_travel3D.GPScoord[i].x));
                                printf("\nPls enter the y coordinate of point %d ",i+1);
                                scanf("%f",&(ptr_dist_travel->dist_travel3D.GPScoord[i].y));
                                printf("\nPls enter the z coordinate of point %d ",i+1);
                                scanf("%f",&(ptr_dist_travel->dist_travel3D.GPScoord[i].z));
                        }  
                        break;   
                }
        }

}
void dist_cal(union Euc_dist *ptr_dist_travel,int choice)
{
        
        int i;
        float temp_deltax,temp_deltay,temp_deltaz;

       
        switch (choice)
        {
                case 1:
                {       
                        ptr_dist_travel->dist_travel2D.total_distance=0.0;
                        for (i=0;i<(maxsize-1);++i)
                        {
                                temp_deltax=pow((ptr_dist_travel->dist_travel2D.GPScoord[i+1].x-ptr_dist_travel->dist_travel2D.GPScoord[i].x),2);
                                temp_deltay=pow((ptr_dist_travel->dist_travel2D.GPScoord[i+1].y-ptr_dist_travel->dist_travel2D.GPScoord[i].y),2);
                                ptr_dist_travel->dist_travel2D.distance2D[i]=sqrt(temp_deltax+temp_deltay);
                                ptr_dist_travel->dist_travel2D.total_distance += ptr_dist_travel->dist_travel2D.distance2D[i];
                        }
                        break;
                                
                }
                case 2:
                {
                         ptr_dist_travel->dist_travel3D.total_distance=0.0;
                         for (i=0;i<(maxsize-1);++i)
                        {
                                temp_deltax=pow((ptr_dist_travel->dist_travel3D.GPScoord[i+1].x-ptr_dist_travel->dist_travel3D.GPScoord[i].x),2);
                                temp_deltay=pow((ptr_dist_travel->dist_travel3D.GPScoord[i+1].y-ptr_dist_travel->dist_travel3D.GPScoord[i].y),2);
                                temp_deltaz=pow((ptr_dist_travel->dist_travel3D.GPScoord[i+1].z-ptr_dist_travel->dist_travel3D.GPScoord[i].z),2);
                                ptr_dist_travel->dist_travel3D.distance3D[i]=sqrt(temp_deltax+temp_deltay+temp_deltaz);
                                ptr_dist_travel->dist_travel3D.total_distance += ptr_dist_travel->dist_travel3D.distance3D[i];
                        }
                        break;
                }
        }
}
void print_dist(union Euc_dist *ptr_dist_travel,int choice)
{
        int i;

        printf("\n------------------------------------------------------------");
        printf("\nDistance travelled between two GPSpoints in %d dimension",choice+1);
        printf("\n------------------------------------------------------------");
        switch (choice)
        {
                case 1:
                {
                        for (i=0;i<(maxsize-1);++i)
                        {
                                printf("\nDistance travelled between point %d and point %d is %f ",i+1,i+2,ptr_dist_travel->dist_travel2D.distance2D[i]);
                        }
                        printf("\n Total distance travelled in 2D dimension is %f : ", ptr_dist_travel->dist_travel2D.total_distance);
                        break;
                }
                case 2:
                {
                        for (i=0;i<(maxsize-1);++i)
                        {
                                printf("\nDistance travelled between point %d and point %d is %f ",i+1,i+2,ptr_dist_travel->dist_travel3D.distance3D[i]);
                        }
                        printf("\n Total distance travelled in 3D dimension is %f : ",ptr_dist_travel->dist_travel3D.total_distance);
                        break;
                }
        }
}