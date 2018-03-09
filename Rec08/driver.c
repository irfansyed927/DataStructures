/**************************** driver.c  ***********************/

#include "list.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{
   listADT X, Y, Z; // declaring the list 
   char *name = "List";
   int a, value; 
 
   X = NewList(); //Creating a new list X
   Y = NewList(); // Creating a new list Y

    printf("Enter the Values:\n"); 
    
    int i; 
	for (i = 0; i < 6; i++)
       {
	  scanf("%d", &a);
	  list_insert_sorted(X, a); // sorting the values 
	  list_insert_unsorted(Y, a);

}

   printf("Print X Values:\n"); // printing X values 
   list_print_values(X, name);

   printf("Print Y Values:\n"); // print Y values 
   list_print_values(Y, name);

   printf("Average value of X %lf\n", list_average(X)); // printing the average of X
   printf("Average value of Y %lf\n", list_average(Y)); // printing the average of Y

   printf("Enter the value to delete\n");
   scanf("%d", &a);

   list_delete_by_value(X, value);
   list_delete_by_value(Y, value);

   printf("Print X values again\n");
   list_print_values(X, name);

   printf("Print Y values again\n");
   list_print_values(Y, name);

   printf("Average value of X %lf\n", list_average(X));
   printf("Average value of Y %lf\n", list_average(Y));

   Z = list_n_copy(X,3);
   printf("Print Z values:\n");
   list_print_values(Z, name);
   printf("Average of Z %lf\n", list_average(Z));
   
	return 0; 
}
