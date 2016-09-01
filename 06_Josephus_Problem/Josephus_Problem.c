/*
	Author		:	Tarun Jain
	Roll No.	:	MT2015120
	College		:	IIITB
	Email		:	Tarun.Jain@iiitb.org
	Program		:	Josephus Problem, For N people and Killing 'K'th Person everytime.
	Statement	:	In computer science and mathematics, the Josephus Problem (or Josephus permutation) is a theoretical problem. 					Following is the problem statement:

				There are n people standing in a circle waiting to be executed. The counting out begins at some point in the 					circle and proceeds around the circle in a fixed direction. In each step, a certain number of people are 					skipped and the next person is executed. The elimination proceeds around the circle (which is becoming smaller 					and smaller as the executed people are removed), until only the last person remains, who is given freedom. 					Given the total number of persons n and a number k which indicates that k-1 persons are skipped and kth person 					is killed in circle. The task is to choose the place in the initial circle so that you are the last one 				remaining and so survive.

				For example, if n = 5 and k = 2, then the safe position is 3. Firstly, the person at position 2 is killed, then 				person at position 4 is killed, then person at position 1 is killed. Finally, the person at position 5 is 					killed. So the person at position 3 survives.
				If n = 7 and k = 3, then the safe position is 4. The persons at positions 3, 6, 2, 7, 5, 1 are killed in order, 				and person at position 4 survives.
				
				Recursive Function : 	josephus(n, k) = (josephus(n - 1, k) + k-1) % n + 1
  							josephus(1, k) = 1

	NOTE 		: 	This is not a recursive program, This program is made using circular linked list. 

*/

// Header Files
#include <stdio.h>
#include <stdlib.h>

// Macros
#define EFO	printf("\n--------------------------------\n");


// Structures
struct node
{
	int data;
	struct node *prev;
	struct node *next;
	//struct node killed;		// Assuming Some future expansion
};

// Global Variables

// Function Prototype
int solveJosephus( int n, int k);
void display( struct node* head);
struct node* elimination( struct node* track, int k, struct node** head);

// Main Function
int main()
{
	// Variables
	int n, k;
	int ch = 1;
	int result;
	
	// Read Input
	do
	{
		EFO;
		printf("\nWelcome to Joseph Us Problem\n");
		printf("\nEnter the Value of N : ");
		scanf("%d", &n);
		printf("\nEnter the Value of K : ");
		scanf("%d", &k);
		
		// Run Josephus Problem Function
		if( k == 0)
		{
			printf("\nInvalid Entry\n");
			exit(0);
		}
		result = solveJosephus(n, k);
		if( result == 0)
			printf("\nNo Person Left. All Killed !!!\n");
		else
			printf("Last Person Remaining is : %d", result);
		
		EFO;
		printf("\nWanna Try Again ???\nPress 1 to continue ...To Exit Enter any other number : : ");
		scanf("%d", &ch);
	}while( ch == 1);
	
	return 0;
}

// Solve Josephus Function
int solveJosephus( int n, int k)
{
	// Variables
	int i;
	int count = n;
	
	// If only single person and k = 1
	if(count == 1 && k == 1)
		return 0;
	else if( count == 1 && k != 1)
		return 1;
		
	// Circular Link List
	struct node *head, *track;
	
	// Creating Head Node
	head = (struct node *) calloc( 1, sizeof(struct node));
	head -> data = 1;
	head -> prev = NULL;
	head -> next = NULL;
	
	track = head;
	
	// Creation 
	for( i = 2; i <= n; i++)
	{
		track -> next = (struct node *) malloc ( sizeof(struct node));
		track -> next -> prev = track;
		
		track = track -> next ;
		track -> data = i;
		track -> next = NULL;
	}
	
	// Making it Circular
	track -> next = head;
	head -> prev = track;
	
	// Display Circular List
	printf("\nInitial State of People : ");
	display( head);
	
	// Elimination Begins Here
	track = head;
	while( count > 1)
	{
		// Eliminate
		track = elimination( track, k, &head);
		display(head);
		count--;
	}
	
	// Return Remaining Element
	return head -> data;
}

// Display Circular List
void display( struct node *head)
{
	// Tracking Pointer
	struct node *track = head;
	
	// Printing
	do
	{
		printf("  %d", track -> data);
		track = track -> next;
	}while( track != head);
	
	printf("\n");
}

// Kill Function
struct node* elimination( struct node *track, int k, struct node **head)
{
	struct node *temp;
	// Skip K-1 Persons
	while( k-1 != 0)
	{
		track = track -> next;
		k--;
	}
	
	// Update Neighbours of kth Person
	track -> prev -> next = track -> next;
	track -> next -> prev = track -> prev;
	
	printf("\nEliminated Person is : %d\n", track -> data);

	// Updating Head if Head is being Deleted
	if( track == *head)
	{
		*head = track -> next;
		
	}	

	// Pointer for Freeing Memory Purpose
	temp = track;
	// Update New Head For Next Iteration
	track = track -> next;
	
	// Delete Node
	free(temp);
	
	// Return New Head for Next Iteration
	return track;
	
}
