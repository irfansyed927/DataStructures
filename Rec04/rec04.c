// Reciation 4 by Irfan Syed 

#include <stdio.h>
#include <stdlib.h>

typedef struct Point
{
  double x;
  double y;
} PointT; 

typedef struct Rect
{
 PointT location;
 char color; 
 double w; //width
 double h; //height;
} RectT;

int main ()
{
 RectT a, b, *recs;
 int result;
 printf("Enter x cordinate of a\n"); 
 scanf("%lf", &a.location.x);
 printf("Enter y cordinate of a\n");
 scanf("%lf", &a.location.y);
 printf("Enter Width of a\n");
 scanf("%lf", &a.w);
 printf("Enter Height of a\n");
 scanf("%lf", &a.h); 

 printf("\n"); 
 printf("Enter x cordinate of b\n");
 scanf("%lf", &b.location.x);
 printf("Enter y cordinate of b\n");
 scanf("%lf", &b.location.y);
 printf("Enter Width of b\n");
 scanf("%lf", &b.w);
 printf("Enter Height of b");
 scanf("%lf", &b.h);
 
 result=chk_overlap(&a, &b);
 if(chk_overlap(a,b))
printf("\nRectangle a and b overlaps.\n\n");
else 
printf("\nRectangle a and b doesnt overlaps.\n");
 return 0; 

recs = (RectT *)malloc(50*sizeof(RectT));
 int i;
 for (i=0; i<50; i++)
{
 recs[i].location.x = rand()%20;
 recs[i].location.y = rand()%20;
 recs[i].w = rand()%20;
 recs[i].h = rand()%20;
}

 printf("Randomly generated 50 triangles.\n\n");
 int counta = 0;
 int countb = 0; 
 for ( i = 0; i < 50; i++)
{
 if (chk_overlap(a, recs + i)) counta++;
 if (chk_overlap(b, recs + i)) countb++;
}

printf("Total number of Rectangles overlapping with a is %d\n", counta);
printf("Total number of Rectangles overlapping with b is %d\n", countb); 
printf("Total number of Rectangles overlaping with a and b is %d\n", counta + countb);
}

int chk_overlap(RectT *r1, RectT *r2)
{

if (r1-> location.x <= r2 -> location.x && r2->location.x <= r1->location.x + r1 -> w && r1-> location.y <= r2-> location.y && r2->location.y <= r1->location.y + r1 -> h)

return 1; 

else 
 
return 0; 
}
  
