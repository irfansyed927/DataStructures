// Homework 5 By irfan Syed 
//In this assignment you are asked to write a sample driver program and set of functions that can perform on a binary search tree. 

#include <stdio.h>
#include <stdlib.h>

struct TreeNode;
typedef struct TreeNode { // creating a struct for binary tree 
  int element; // data value which will be integers.
  struct node *left, *right; //declaring the left and right pointer in the nodes
}*root

typedef struct TreeNode *node;

typedef int ElementType;


// prototype functions 
void node insert(ElementType, node); // Inserting 

void node delete(ElementType, node);  // Deletion

void node findmin(node);  // Finding the min value 

void node findmax(node);

void node find(ElementType, node); // finding the treet 

void display(node, int);
// Program will ask user to enter a command and related parameters in a loop 

void main()
{
   int ch; // declaring it for switch function 
   ElementType a;
   node temp; 

	while (1) // loop 
     {
	printf("\n1. Insert\n2. Delete\n3. Find\n4. Find min\n5.FindMax\n6.Display\n7. List preorder\n8. List postorder\n9.List Levelorder\n10. Height\n11. Sum\n12. Quit\nEnter Your Choice:");

	scanf("%d", &ch);
 
	switch(ch)

{
     // cases for the command and related parameters 
	case 1:

	printf("Enter an element : "); 

	scanf("%d", &a);

	root = insert(a, root);  // caling insertion function 

	break;

	case 2:

	printf("\nEnter the element to delete : ");

	scanf("%d",&a);

	root = delete(a, root); // calling deletion function 

	break;

	case 3:

	printf("\nEnter the element to search : ");

	scanf("%d",&a);

	temp = find(a, root); // find fuction 

	if (temp != NULL)

	printf("Element found");

	else

	printf("Element not found");

	break;

	case 4:

	temp = findmin(root);  // finding the min numbers in the tree

	if(temp==NULL)

	printf("\nEmpty tree");

	else

	printf("\nMinimum element : %d", temp->element);

	break;

	case 5:

	temp = findmax(root);  // finding the max 

	if(temp==NULL)

	printf("\nEmpty tree"); // error to show that tree is empty 

	else

	printf("\nMaximum element : %d", temp->element);

	break;

	case 6:

	if(root==NULL)

	printf("\nEmpty tree"); // error to show if the tree is empty at first 

	else

	display(root, 1); // calling display function 

	break;

	case 7:

	printpreorder(root); // calling preorder function 

	break;

	case 8:

	printinorder(root);

	break;

	case 9:

	printpostorder(root);

	break;

	case 10:

	exit(0);

	default:

	printf("Invalid Choice");

   }

  }

}



void insert(ElementType x,nodeT) // Insertion function 

{

	if(t==NULL) // if The root is empty 

{

	t = (node)malloc(sizeof(node)); // crate a node dynamically 
	
	 t->element = x; // assign the value 

	 t->left = t->right = NULL; // make the right subtree and left subtree null

}

     else

{

     if(x < t->element)  // if the values are smaller the element will go in the left subtree

	t->left = insert(x, t->left); 

     else if(x > t->element) // elements are bigger than it goes in the right subtree

	t->right = insert(x, t->right);

}

return t;

}



void delete(ElementType x,nodeT) // deleting a node 

{

node temp; // declaring a temp

if(t == NULL)  // if the root is null then no element found 

printf("\nElement not found");

else

{

if(x < t->element)

	t->left = delete(x, t->left); // caling function recursive

  else if(x > t->element) // if deleting the left subtreet or node  

	t->right = delete(x, t->right);

  else

{

    if(t->left && t->right)

{

	temp = findmin(t->right); // case 2 children find the min value on right subtreet and replace the node value copy and delete 

	t->element = temp->element;

	t->right = delete(t->element,t->right);

 }

  else if(t->left == NULL)

	t=t->right;

  else

	t=t->left;

   }

}

   return t;

}

void makeempty()

{

	root = NULL;

}



void findmin(node temp)

{

	if(temp == NULL || temp->left == NULL) // if left is null then return temp

	  return temp;

	return findmin(temp->left); // calling recursivley 

}



void findmax(node temp)

{

	if(temp==NULL || temp->right==NULL)

	 return temp;

     return findmax(temp->right);

}



void find(ElementType x, nodeT)

{

    if(t==NULL) return NULL;

	if(x<t->element) return find(x,t->left);

	 if(x>t->element) return find(x,t->right);

return t;

}



void display(node *t,int level)

{

int i;

if(t)

{

display(t->right, level+1);

	printf("\n");

	for(i=0;i<level;i++)

	printf(" ");

	printf("%d", t->element);

	display(t->left, level+1);

 }

}
 
  void printpreorder(node*T)  // printing the pre order 

{

if(T != NULL)

{

	printf("%d ", T->element);

	printpreorder(T->left); // calling function recursivley 

	printpreorder(T->right); // printing the right subtree

  }

}



void printinorder(node*T)

{

	if(T != NULL)

{

	printinorder(T->left); //printing the left subtree first 

	printf("%d ", T->element); // print statement will print the values 

	printinorder(T->right);  // printing the right subtree after 

  }

}



void printpostorder(node *T)

{

    if(T != NULL)

{

	printpostorder(T->left); // first print the left subtree 

	printpostorder(T->right); // print the right subtree 

	printf("%d ", T->element); // print the root value after that 

   }

}


