#include <stdio.h>
#include "set.h"
#include <stdlib.h>

//defines a node structure to use to point to nxt link in list
typedef struct node {
setElementT val;
struct node *nxt;
} NodeT;

struct setCDT {
NodeT *start;
NodeT *end;
int cnt;
};

setADT setNew() 
{
  setADT set = (setADT) malloc(sizeof(struct setCDT));
  if(set == NULL) //if no values are within the set then it returns NULL
  {
	return NULL; 
  } 
  set->start = set->end = NULL;
  set->cnt = 0;
  return set;
}

void setPrint(setADT s, char *name) 
{
  //creates a node to current point
  NodeT *crr;
  //points current pointer to being of set s
  crr = s->start;
  //prints the beginning of the set
  printf("=Set %s: [", name);
  while(crr) 
  {
     printf("%d", crr->val);

     crr = crr->nxt;
	 if(crr != NULL)
	 {
	    printf(", ");
	 }
  }
  printf("]=\n");
}

void setFree(setADT s) 
{
  //creates two nodes to traverse the link
  NodeT *crr, *tmp;
  //sets current point to beginning of set s
  crr = s->start;
  while(crr) 
  {
    tmp = crr->nxt;
    free(crr);
    crr = tmp;
  }
  free(s);
}

int setInsertElementSorted(setADT s, setElementT x) 
{
  //creates nodes to allow for traversal of set
  NodeT *crr, *prv, *tmp;
  //allocates memory for a temporary node
  tmp = (NodeT *) malloc(sizeof(NodeT));
  if(tmp == NULL) 
  { 
    return 0; 
  } 
  tmp->val = x;
  
  tmp->nxt = NULL;
  prv = NULL;
  crr = s->start;
  while(crr) 
  {

    if (crr->val == tmp->val) 
	{
      return s->cnt; 
    }
	else if(crr->val > tmp->val) 
	{
      break;
    }
    else 
	{
      prv = crr;
      crr = crr->nxt;
    }
  }
if(prv == NULL) 
  {
    tmp->nxt = s->start;
    s->start = tmp;
    s->cnt++;
  }
  else 
  {
    tmp->nxt = prv->nxt;
    prv->nxt = tmp;
    s->cnt++;
  }

  if(tmp->nxt == NULL) 
  {
    s->end = tmp;
  }

  return s->cnt;
}

setADT setUnion(setADT A, setADT B) 
{
  //initalizes a current node for traversal
  NodeT *crr;
  //initalizes a new set C
  setADT C = setNew();
  //points current node to start of set A
  crr = A->start;
  while(crr) 
  {
    setInsertElementSorted(C, crr->val);
    crr = crr->nxt;
  }
  crr = B->start;
  //conditonal to merge set B into set C until current node points to a NULL value
  while(crr) 
  {
    setInsertElementSorted(C, crr->val);
    crr = crr->nxt;
  }
  
  return C;
}

setADT setIntersection(setADT A, setADT B) 
{
  //initliazes two current nodes for traversal of set A and B seperately
  NodeT *crr_a, *crr_b;
  
  setADT intersection = setNew();
  
  crr_a = A->start;
  
  while(crr_a) 
  {
	//points current node for set B to beginning of set B
    crr_b = B->start;	
    while(crr_b) 
	{
	  
      if(crr_a->val < crr_b->val) 
	  {
        break;
      }
	  
      else if(crr_a->val == crr_b->val) 
	  {
        setInsertElementSorted(intersection, crr_a->val);
        crr_b = crr_b->nxt;
      } 
      else 
	  {
        crr_b = crr_b->nxt;
      }
    }
    crr_a = crr_a->nxt;
  }
  return intersection; 
}
setADT setDifference(setADT A, setADT B) 
{
  //creates nodes for a current pointer for set A and B
  NodeT *crr_a, *crr_b;
  setADT diff = setNew();
  crr_a = A->start;
  //conditional used to determine traverse link list A until current node points to a NULL Value
  while(crr_a) 
  {
    crr_b = B->start;
	
    while(crr_b) 
	{
      if(crr_a->val == crr_b->val) 
	  {
        break;
      }
	  else if(crr_a->val < crr_b->val) 
	  {
        setInsertElementSorted(diff, crr_a->val);
        break;
      }
      else 
	  {
        crr_b = crr_b->nxt;
      }
    }
    if(crr_b == NULL) 
	{
      while(crr_a) 
	  {
		//creates a sorted set of the determine difference in values
        setInsertElementSorted(diff, crr_a->val);
        crr_a = crr_a->nxt;
      }
      break;
    }
    else 
	{
      crr_a = crr_a->nxt;
    }
}
return diff;
}
//function used to determine the cnt of set s
int setCardinality(setADT s) 
{
  return s->cnt;
}

