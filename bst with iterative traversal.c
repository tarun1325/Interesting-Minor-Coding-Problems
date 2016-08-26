/*
	Author	:	Tarun Jain
	Roll No.	:	MT2015120
	Program	:	Binary Search tree Creation and Iterative Preorder, PostOrder and InOrder Traversal
	Date	: 	25- Aug-2016
	Assumption :	Maximum Number of Nodes allowed is 100 - MAX_SIZE
*/

// Header Files
#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Structure of Node
struct Node
{
	int data;
	struct Node *left;
	struct Node *right;
};

// Structure of Stack 
struct Stack
{
	struct Node *stk[MAX_SIZE];
	int flag[MAX_SIZE];
	int top;
};

// Global Variables
struct Node *head = NULL;
struct Stack s;

// Function Prototype
void createBST( int);
void push( struct Node *, int );
struct Node* pop();
void inorder( struct Node*);
void preorder( struct Node*);
void postorder(struct Node*);

// Main Function
int main()
{
	// Variables
	int symbol_inserted;
	int input = 1;
	s.top = -1;				// Stack Top initialization

	
	// Input 
	// Insert into BST
	while( input == 1)
	{	// Asking User to Input Data
		printf("\nEnter the Element : ");
		scanf( "%d", &symbol_inserted); 		
		
		// Creating BST		
		createBST( symbol_inserted);	
		
		// Asking User's Preference for Inserting More Elements
		printf("\nWant to Insert More Elements , Press 1 , Else Press any other key: ");
		scanf("%d", &input);	
	}
	
	// Pre order Traversal
	printf( "\n Preorder Traversal is :\n");
	preorder( head);
	 
	// Post Order Traversal
	printf( "\n Postorder Traversal is :\n");
	postorder( head);
	
	// In Order Traversal
	printf( "\n Inorder Traversal is :\n");
	inorder( head);
	
	return 0;
}

// Function to Create BST
void createBST( int data)
{

	// Creating New Node
	struct Node *new;
	new = ( struct Node *) malloc( sizeof(struct Node));
	new -> data = data;
	new -> left = NULL;
	new -> right = NULL;
	
	// First Node
	if( head == NULL)
	{
		head = new;
	}
	// Inserting Other Nodes
	else
	{
		// Pointer to traverse BST to Find Position to Insert
		struct Node *track = head;

		while( track != NULL)
		{
			if( (track -> data) >= data )
			{
				if( track -> left == NULL)
				{	track -> left = new;
					return;
				}
				else
					track = track -> left;
			}
			else
			{
				if( track -> right == NULL)
				{
					track -> right = new;
					return;
				}
				else
					track = track -> right;
			}
		}
	}
}

// Stack Push Function
void push( struct Node *element, int flag)
{
	if( s.top == ( MAX_SIZE - 1))
	{
		printf("\nStack is Full\n");
	}
	else
	{
		s.top++;
		s.stk[ s.top] = element;
		s.flag[s.top] = flag;
	}
}

// Stack Pop Function
struct Node* pop()
{
	if( s.top == -1)
	{
		printf("Stack is empty");
		return NULL;
	}
	else
		return ( s.stk[ s.top--] ); 
}

// In-Order Traversal Function
void inorder( struct Node *temp)
{
	while( temp != NULL  ||  s.top > -1 )
	{
		if( temp) 
		{
			push( temp, 0);					// Push Root 
			temp = temp -> left;				// Go to Left
		}
		else
		{
			temp = pop();						// Pop  
			printf("%d ", temp -> data);			// Print
			temp = temp -> right;				// Go to RIght
		}
	}
}

// Pre Order Traversal
void preorder( struct Node *temp)
{
	while ( temp != NULL || s.top > -1 )
	{
		if( temp)
		{
			printf( "%d ", temp -> data);			// Print Root
			push( temp, 0);					// Push Root
			temp = temp -> left;				// Go to Left
		}
		else
		{
			temp = pop();						// Pop
			temp = temp -> right;				// Go to Right
		}
	}
}

// Post Order Traversal
void postorder( struct Node *temp)
{
	while( temp != NULL || s.top > -1 )
	{
		if( temp)
		{
			push( temp, 0);
			temp = temp -> left;
		}
		else
		{
			temp = pop();
			if( s.flag[ s.top + 1] == 0)
			{
				push( temp, 1);
				temp = temp -> right;
			}
			else
			{
				printf( "%d ", temp -> data);
				temp = NULL;
			}
		}
	}
}
