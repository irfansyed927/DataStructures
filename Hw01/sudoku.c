// Homework 1 by Irfan Syed 
// Declaring data structure to represent a Sudoku puzzle 

#include <stdio.h>
#include <stdlib.h>
 

//Prototype functions 
void getpuzzle(char fillpuzzle[][9]);
void printSudoku(char valuepuzzle[][9]);
void solvePuzzle(char [][9]);
char puzzle[9][9];

int main()
{
  int Userchoice;
 

//Ask User if he/she wants to enter data for sudoku puzzle or a sudoku solution.
   while (Userchoice !=1 || Userchoice !=2)
 {
	printf("Input 1 for puzzle, Input 2 for solution\n");
	scanf("%d", &Userchoice); 
   if (Userchoice == 1 || Userchoice == 2)
 {
	// put functions here
	if (Userchoice == 1)
 {
	getpuzzle(puzzle);
	printSudoku(puzzle);
	solvePuzzle(puzzle);
	break;
   }
    else
   {
// if user enter number 2
	getpuzzle(puzzle);
	printSudoku(puzzle);
	solvePuzzle(puzzle);
	break;
	}
    }
   else
   {
	printf("Invalid Response!\n");
   }
	
 }
}

// get puzzle 

void getpuzzle(char fillpuzzle[][9])
{
  int i , j , tmp;
  for (i = 0; i<9 ; i++)
{
	for (j = 0; j<9 ; j++)
{
	scanf("%d", &tmp);
	fillpuzzle[i][j] = tmp;
  }
 }
}
// print sudoku values 
void printSudoku(char valuepuzzle[][9])
{
  int i, j;
	for(i = 0; i < 9; i++)
    {
  printf("\n");
    {
	for (j=0; j<9; j++)
    {
  printf("%d", valuepuzzle[i][j]);
    }
  printf("\n");
  }
 }	 
}

void solvePuzzle(char [][9])
{
int count[10] = {0};
	for(int i = 0; c; i < 9; i++){
	c = i/3*3;
	 for(int j = 0; j < 9; j++){
	r = j/3*3;
	if(puzzle[i][j]) continue;
	for(int k = 0; k<9; k++){
	 count[puzzle[i][k]] ++;
	count[puzzle[k][j]]++;
  }
	
	for(int i = c; i < c+3; i++){
	  for(int j = r; j<r+3; j++){
		count[puzzle[i][j]]++;
	}
     }
  printf("[%d][%d]: ", i , j);
	for(int k =1; k < 10; k++){
	 if(!count[k]){
		printf("%d" , k);
      }
	count[k] = 0;
    }
	printf("\n");
   }
}
