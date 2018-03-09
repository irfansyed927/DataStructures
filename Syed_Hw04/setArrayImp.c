#include <stdio.h>
#include "set.h"
#include <stdlib.h>


#define Max 100

// Structs 

struct setCDT {
setElementT *x;
int count; 
int size;
}

// Implementation 

setADT setNew()
{
  setADT set; 
  set = malloc(sizeof(*set));
  set->count = 0;
  set ->size = Max;
  return set;
}

void setPrint(setADT s, char *name) 
{
  int i;
  printf("Set %s: [", name);
  for(i = 0; i < s->count; i++) 
  {
    printf("%d", s->x[i]);
	if((i+1) < s->count)
	{
		printf(", ");
	}
  }
  printf("]\n");
}

void setFree(setADT s) 
{
  free(s->x);
  free(s);
}

int setInsertElementSorted(setADT s, setElementT e) 
{
  int i, j, k, tmp;
  if(s->count == s->size) 
  {
    setExpandSize(s, s->size * 2);
  }
  // Insert first element
  if(s->count == 0) 
  {
    s->values[s->count] = e;
    s->count++;
    return s->count;
  }
  // Insert sorted element
  for(i = 0; i < s->count; i++) 
  {
    tmp = s->x[i];
    if(tmp == e) 
	{
      return 0; // Insertion failed: the element already exists.
    }
    else if(tmp > e) 
	{
      // We need to move all elements one spot to the right to fit the new value.
      for(j = s->count - 1, k = j + 1; j >= i; j--, k--) 
	  {
        s->x[k] = s->x[j];
      }
      // Place the current element at the last index we left off before moving.
      s->x[i] = e;
      s->count++;
      return s->count;
    }

setADT setUnion(setADT A, setADT B) 
{
  setADT unin = setNew();
  int i;
  for(i = 0; i < A->count; i++) 
  {
    setInsertElementSorted(unin, A->x[i]);
  }
  for(i = 0; i < B->count; i++) 
  {
    setInsertElementSorted(unin, B->x[i]);
  }
  return unin;
}

setADT setIntersection(setADT A, setADT B) 
{
  setADT inter = setNew();
  int i, j;
  for(i = 0; i < A->count; i++) 
  {
    for(j = 0; j < B->count; j++) 
	{
      if(A->x[i] == B->x[j]) 
	  {
        setInsertElementSorted(inter, A->x[i]);
      }
      else if (A->x[i] < B->x[j]) 
	  {
        break; // Element in B is bigger, meaning A[i] does not exist.
      }
    }
  }
  return inter;
}

setADT setDifference(setADT A, setADT B) 
{
  setADT diff = setNew();
  int i = 0, j;
  while(i < A->count) 
  {
    j = 0;
    while(j < B->count) 
    {
      if(A->x[i] < B->x[j]) 
	  {
        setInsertElementSorted(diff, A->x[i]);
        break;
      }
      else if(A->x[i] == B->x[j]) 
	  {
        break;
      }
      else 
	  {
        j++; // Keep iterating. The value might be in a higer index.
      }
   }
    // Insert the rest of the elements, B does not contain any similar vals.
    if(j == B->count) 
    {
      while(i < A->count) 
	  {
        setInsertElementSorted(diff, A->x[i++]);
      }
      break;
    }
    // Keep comparing the rest of the elements
    else 
    {
      i++;
    }
  }
  return diff;
}
int setCardinality(setADT s) 
{
  return s->count;
}
void setExpandSize(setADT s, int size) 
{
  setElementT *new_x;
  int i;
  if(size <= s->size) { return; }
  new_values = (setElementT *) malloc(size * sizeof(setElementT));
  for(i = 0; i < s->count; i++) 
  {
    new_x[i] = s->x[i];
  }
  free(s->x);
  s->x = new_x;
}
