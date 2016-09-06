/*
	Author 		:	Tarun Jain
	Roll Number	:	MT2015120
	File		: 	Tower_of_Hanoi_Iterative.c
	College		: 	IIITB
	Email		:	Tarun.Jain@iiitb.org
	Program		:	Tower Of Hanoi Implementation with Iterative Appoarch
	Date 		:	26-Aug-2016
	Assumption	:	Works for 2^100 Discs i.e. MAX_SIZE
*/

// Include Files
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_SIZE 100

// Structures
struct node						// Node Structure
{
	int data;
	struct node *next;
} ;

// Stack to Push the State of towers
struct Stack
{
	struct node **src[ MAX_SIZE];
	struct node **des[MAX_SIZE];
	struct node **aux[MAX_SIZE];
	int numOfDisc[ MAX_SIZE];
	int top;
};

struct Stack stk;
// Function Prototype
void print_Towers( struct node *A, struct node *B, struct node *C);

// Global Variables
struct node *tower0, *tower1, *tower2;		// Pointers to Towers



void push( int n, struct node **s, struct node **d, struct node **a)
{
	if( stk.top == (MAX_SIZE))
	{
		printf(" Stack Full");
		exit(0);
	}
	else
	{
		stk.top++;
		stk.src[ stk.top ] = s;
		stk.des[ stk.top] = d;
		stk.aux[ stk.top] = a;
		stk.numOfDisc[ stk.top] = n;
	}
}

// Stack Pop Function
void pop( int *n, struct node ***s, struct node ***d, struct node ***a)
{
	if( stk.top == -1)
	{	
		printf("Stack is empty");
		exit(0);
	}
	else
	{
		*n = stk.numOfDisc[ stk.top];
		*s = stk.src [ stk.top];
		*d = stk.des [ stk.top];
		*a = stk.aux [stk.top];
		stk.top--;
	}
}

void tower_of_hanoi( int numOfDisc, struct node** src, struct node **des, struct node **aux)
{
	char ch1, ch2;
	
	struct node **temp = NULL;
	struct node *temp1 = NULL;
	struct node *temp2 = NULL;
	
	// Iterative Inorder Traversal Concept Used
	while( numOfDisc > 0  ||  stk.top > -1)
	{
		// If Number of Disc more than 0
		if( numOfDisc > 0)
		{
			// Push Current state on to Stack
			push( numOfDisc, src, des, aux);
			// Go to Left Subtree
			// For Tower of Hanoi - Left Child has exchanged destination and auxillary
			// Swap them
			temp = aux;
			aux = des;
			des = temp;
			temp = NULL;
			numOfDisc--;

		}
		// If Number of States readched 0
		else
		{
			// Pop Out last state of Towers
			pop( &numOfDisc, &src, &des, &aux);	
			
			// Getting Names of Source and Destination Towers
			if( *src == tower0)
				ch1 = 'A';
			else if( *src == tower1)
				ch1 = 'B';
			else if( *src == tower2)
				ch1 = 'C';

			if( *des == tower0)
				ch2 = 'A';
			else if( *des == tower1)
				ch2 = 'B';
			else if( *des == tower2)
				ch2 = 'C';
				
			// Source to Destination Transition - Movement of Disc
			printf("\n----------------------------------- \n");
			printf("Moving Disc from %c to %c \n", ch1, ch2);
		
			temp1 = *src;
			temp2 = *des;
			*src = temp1 -> next;
			*des = temp1;
			temp1 -> next = temp2;
			temp1 = NULL;
			temp2 = NULL;

			// Print New State of Trees after Movement
			print_Towers(tower0, tower1, tower2);

			// Right Subtree
			// Right Side of Tower of Hanoi has Source and Auxillary Exchanged
			// Swap them
			numOfDisc--;
			temp = src;
			src = aux;
			aux = temp;
			temp = NULL;
	
		}
		
	}
}


// Main Function
int main()
{

	// Variables
	int numOfDisc;
	int i;

	// Initialize the Towers
	tower0 = tower1 = tower2 = NULL;
	stk.top = -1;
    
	// Read Input
	printf("\nEnter No. of Disc : ");
	scanf("%d", &numOfDisc);
	while( numOfDisc > pow(2,MAX_SIZE))
	{
		printf("\nNumber of Discs exceeded!!! \n\nEnter No. of Disc under %d : ",  pow(2,MAX_SIZE));
		scanf("%d", &numOfDisc);
	}
	printf("\nSteps For Constructing Tower of Hanoi for %d Discs...\n\n", numOfDisc);

	// Creating N - discs
	for( i = numOfDisc ; i > 0 ; i--)
	{
		// Create Disc Node
		struct node *temp = (struct node *) calloc( 1, sizeof( struct node)) ;
		temp->data = i ;

		// Insert Node into first tower initially
		temp->next = tower0;
		tower0 = temp;
	}
	// Print Towers
	print_Towers( tower0, tower1, tower2);

	// Call to Iterative Logic
	tower_of_hanoi( numOfDisc, &tower0, &tower1, &tower2);
	return 0;
}

// Print Towers Function
void print_Towers( struct node *A, struct node *B, struct node *C)
{
	printf("\nA\tB\tC\n\n");
	while((A !=NULL)  ||  ( B  !=NULL )  || ( C  !=NULL ))
	{
		if( A !=NULL )
		{
			printf( "%d", A->data  );
			A = A->next;
		}
		printf("\t");
		if(  B  !=NULL )
		{
			printf( "%d", B->data  );
			B = B->next;
		}
		printf("\t");
		if( C  !=NULL)
		{
			printf( "%d", C->data  );
			C = C->next;
		}
		printf("\n");
	}
}

