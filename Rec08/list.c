/******************************* list.c ***********************/
#include "list.h" 
#define NULL 0
typedef struct point {
   listElementT x; 
   struct point *next;
} myDataT;

struct listCDT {
	myDataT *start; // myDataT *header;
	myDataT *end;   // myDataT *foother;
};

listADT NewList()
{
   listADT tmp;
   tmp = (listADT)malloc(sizeof(struct listCDT)); // New(listADT);

   if (tmp==NULL) 
    return NULL;                  

   tmp->start = tmp->end = NULL;
   return tmp;
}

// Prototype functions for Driver file 

void list_print_values(listADT a, char *name)
{
  while(a->start)
 {
	printf("%d", a->start->x);
	 a->start = a->start->next;
 }
}

void FreeList(listADT a)
{

 if(a== NULL){
  
 return;
 }
    myDataT *curr, *temp;
     curr = a->start;
       while (curr != NULL){
	  temp = curr -> next;
		free(curr);
	}
	  free(a);
  }

void list_delete_by_value(listADT a, listElementT x)
{
  myDataT *curr, *prev;
  prev = NULL; // there are no previous right now. 
  curr = a->start;
   
     while (curr->x != x)
      {
	prev = curr; 
	curr = curr -> next; 
	}
     if (prev == NULL){
	a->start = curr->next;
	}
        else {
        prev->next = curr -> next; 
         free(curr);  // deeleting the value 
       }
}	

listADT list_n_copy(listADT a, int n)
{

  listADT Z;  //creating a new list 

   Z = NewList();
   myDataT *curr;
   curr = a->start; // declaring the starting point 
    int count; 

	while(curr != NULL) {
	  if(count == 3)
	    break;
    list_insert_unsorted(Z, curr->x);
    curr = curr -> next; 
    count++;
     }
    return Z;
 }

























