// Recitation 6 By irfan Syed 
// Use random.h interface and random.c implementation 

#include <stdio.h>
#include "random.h"
#include <stdlib.h> 
// include "genlib.h"
#define Array_length 4 

void digitGuess(int s, int *arr); // prototype 
int digitSecret(int n); 
int compareDigits(int arr1, int arr2);




int main(void)
{

 int secret; 	// declare variable
 Randomize(); 
 while(1)
 {
   secret = RandomInteger(1000, 9999);
	printf("%d",secret);
  int *solution = digitSecret(secret);
   if (solution != NULL)
  {
	digitGuess(secret, solution);
 }	
}

int *digitSecret(int n)
{
  int i = 0;
  int checking; 
  int *s_a = malloc (sizeof (int) * Array_length); 
  while ( n > 0) {
   s_a [(Array_length)] = n % 10;
   n = n/ 10;  
   i++; 
 }  
  checking = differentDigits(s_a);  // put the new function here 

  if (checking == 0)
 {
	return NULL; 
 }
  else 
 {
 	return s_a;
 }
  free(s_a);

}

int differentDigits(int *intArray)
{
   int s[4];
   int i; 
   for (i = 0; i < Array_length; i++)
   {
	s[i]= *(intArray + i);
   }
   
   if(s[0] == s[1] == s[2] == s[3])
   {
	return 0; 
   }
  else 
  {
  	return 1;
  }
}

int *compareDigits(int *arr1, int *arr2)
{
  int i, j; 
  int count1 = 0, count2 =0, count3 = 0;
  static int digitCountArr[3]; // Check this one 

  for (i = 0; i < Array_length; i++)
 {
 	for (j = 0; j < Array_length; j++)
	{
		if(*(arr1 + i) == *(arr2 + j))
	 {
		  if (*(arr1 + i) == *(arr2 + i))
	 {
		count1++;
		continue; 
	 }
		else 
	 {
 		count2++; 
		continue; 
	   }
	}
     }
 }

  count3 = Array_length - (count1 + count2); 
  digitCountArr[0]= count1; // count of digit in place 
  digitCountArr[1]= count2; // count of valid digit out of place 
  digitCountArr[2]= count3; // count of digits that do not exist 
  count1 = 0; 
  count2 = 0; 
  count3 = 0; 
  return digitCountArr; 
}

void digitGuess(int s, int *arr)
{
  int i, guess, count; 
  int *solution = NULL; 
  int *digitCounts = NULL; 
  
   for (i = 1; i <= 40; i++){
	count = 0; 
 	while (solution == NULL)
 	{
		printf("Enter your Guess: "); 
		scanf("%d", &guess);
		solution = digitSecret(guess); 
	}
   if (s == guess)
   {
 	printf("\nCong! You Won!\n");
	printf("Solution was: %d", s); 
	printf("\nYour Guess was: %d\n", guess);
	return; 
   }

   else 
   {
	printf("Incorrect TRY Again\n");
	digitCounts= compareDigits(arr, solution);
	if (*(digitCounts + 0) != 1)
 	{
		printf("%d digits are in_place\n", *(digitCounts + 0));
	}
	else 
	{
	 	printf("%d digit is in place\n", *(digitCounts + 0));
	}
	if (*(digitCounts + 1) != 1)
	{
		printf("%d digit is in place\n", *(digitCounts + 1));
	}
	else 
	{
		printf("%d digit is out of place\n", *(digitCounts +1));
	}
	if (*(digitCounts + 2) != 1)
	{
		printf("%d digits do not exist\n", *(digitCounts + 2));
	}
	else 
	{
		printf("%d digit does not exist\n", *(digitCounts + 2));
	}
	digitCounts = NULL;
    }
     solution = NULL; 
   }
  printf("Solution was: %d", s);
  printf("Try again with new number\n");
  return; 
}
	
}












































 

