// Recitation 3 by Irfan Syed 
// Lab Thursday 10-11am 

#include <stdio.h>

main ()
{
   // declare three integer arrays as follows
  int a[50], b[70], c[120];

// implement a function set_array_rand(int x[], int n) and call it to generate the values in array a and b randomly. 
  
  set_array_rand(a, 50);
  set_array_rand(b, 70);

// using the selection_sort(doublex[], int n) function sor the elements in a and b arrays. 

  sELECTION_SORT(a, 50);
  sELECTION_SORT(b, 70); 

// implement a MERGE function and call it as follows to merge the values in arrays a and b into array c such that the values in c will be sorted after merging. 

  mERGE(a, 50, b, 70, c, 120); 

// print the values in array c 
 
  pRINT_ARRAY("Array c", c, 120);
}

void set_array_rand(int x[], int n)
{
// randomly generate elements of x array, 
for (int i = 0; i < n; i++)
	x[i] = rand_int(30, 100);
}

int rand_int(int a, int b)
{
	return rand() % (b-a+1) + a;
}

void sELECTION_SORT(int x[], int n)
{
 int k, j, m; 
 double temp; 

 for ( k = 0; k < n-1; k++){
  m = k;  
	for (j = k+1; j < n; j++){
  if (x[m] > x[j])
  m = j;
}
 temp = x[k];
 x[k] = x[m];
 x[m] = temp;
}
}

void mERGE(int a[], int na, int b[], int nb, int c[], int nc)
{
 int i; 
 for( i = 0; i<nc; i++){
  if( i < na)
   c[i]=a[1];
else 
 c[i] = b[i-na];
}
SELECTION_SORT(c,nc);
}

void pRINT_ARRAY(char *name, int x[], int n)
{
 printf("%s: \n", name);
 int i; 
 for(i=0; i<n; i++){
  printf("%d ", x[i]);
 }
printf("\n");
}
