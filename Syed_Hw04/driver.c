nclude <stdio.h>
#include <stdlib.h>
#include "set.h"

void getValues(setADT s, char *name);
char getUserChoice();


// -- implementation 

int main() 
{
  
  setADT A, B, C;
  
  char userChoice;
  //creates new set A & B
  A = setNew();
  B = setNew();
  
  getValues(A, "A");
  getValues(B, "B");

  //while conditional used to allow user to try multiple functions before quitting program
  while((userChoice = getUserChoice()) != 'Q' && (userChoice != 'q'))
  {
	  
	//case-switch to determine which function the user intends to use
    switch(userChoice) 
	{
      case 'U':
        printf("Union of sets A & B\n");
        C = setUnion(A, B);
        break;
	  case 'u':
        printf("Union of sets A & B\n");
        C = setUnion(A, B);
        break;
      case 'I':
        printf("Intersection of sets A & B\n");
        C = setIntersection(A, B);
        break;
	  case 'i':
        printf("Intersection of sets A & B\n");
        C = setIntersection(A, B);
        break;
      case 'D':
        printf("Difference of sets A & B\n");
        C = setDifference(A, B);
        break;
      case 'd':
        printf("Difference of sets A & B\n");
        C = setDifference(A, B);
        break;
    }
	//prints user filled sets A & B, and then prints set C 
    setPrint(A, "A");
    setPrint(B, "B");
    setPrint(C, "C");
	//frees set C 
    setFree(C);
  }
  //fress sets A & B 
  setFree(A);
  setFree(B);
}
//function used to prompt and store user inputed values
void getValues(setADT s, char *name) 
{
  int userVal;
  while(1) 
  {
     printf("Please input a number for set %s: ", name);
     scanf("%d", &userVal);
     if(userVal < 0) 
	 {
	   //prints full set once a invlaid, or cancellation value is obtained
	   setPrint(s, name);
       break;
     }
	 //inserts userVal into a sorted set
     setInsertElementSorted(s, userVal);
  }
  printf("\n");
}
//fuction used to recieve desired user course of operation, either Union, Inesrtion, 
//Difference, or to quit the program
char getUserChoice() 
{
  
  char buff[256];
  
  while(1) 
  {
     printf("\nPlease enter a command: \n");
     printf(" [U]nion\n");
     printf(" [D]ifference\n");
     printf(" [I]ntersection\n");
     printf(" [Q]uit\n");
     printf("-> ");
     scanf("%s", buff);
     switch(buff[0]) {
      case 'Q':
	  case 'q':
      case 'D':
	  case 'd':
      case 'U':
	  case 'u':
      case 'I':
	  case 'i':
        return buff[0];
    }
}
}
