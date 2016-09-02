/*
			Author		:		Tarun Jain
			College		:		IIITB
			Email		:		Tarun.Jain@iiitb.org
			Program		:		Two Coloring - Color Each Node of the Graph with either White or Black such that adjacent Should not be same Color
								If Can not color then show -1 as output
*/

// Header Files
#include <stdio.h>
#include <stdlib.h>

// Macros

// Node Structure
struct node
{
	int data;
	int color;
	int depth;
};
struct queue
{
	struct node *element;
	struct queue *next;
} *front, *rear;


// Main Function
int main()
{
	// Variables
	int nov, noe, test, test1;								
	int i, j;										// Loop Variables

	scanf("%d", &test);

	for( test1 = 1; test1 <= test; test1++)
	{
		// Read Input
		scanf( "%d %d", &nov, &noe);

		int graph[nov][nov];						// For Storing Graph
		for( i = 0; i < nov; i++)						// Graph Initialization
		{
			for( j = 0; j < nov; j++)
			{
				graph[i][j] = 0;
			}
		}

		struct node *vertex = ( struct node *) malloc ( sizeof( struct node) * nov);
		for( i = 0; i < nov; i++)						// Initializing Vertex
		{
			vertex[i].data = i+1;					// Vertex Data
			vertex[i].color = -1;					// -1 = No Color
			vertex[i].depth =  -1;					// -1 = Depth Not Set By any Parent
		}

		int e1, e2;								// For Reading Edge Data
		int Answer = 0;
		for( i = 0; i < noe; i++)
		{
			scanf("%d %d",  &e1, &e2);
			graph[ e1 - 1][ e2 - 1] = 1;				// Update Graph
		}

		// Logic To Color Node

		// Initializing Vertex 1
		vertex[0].color = 1;
		vertex[0].depth = 0;

		// Initialize Queue
		front = ( struct queue *) malloc( sizeof( struct queue) );
		front -> element = &vertex[0];
		front -> next = NULL;
		rear =front;
		
		while( front != NULL)
		{
			int current = front -> element -> data - 1;
			// Inserting Neighbours in Queue
			for( i = 0; i < nov; i++)
			{
				// Edge Exist
				if( graph[current ][i] == 1 )
				{
					// Not Processed Until Now
					if(  vertex[i].color != -1)
					{
						if( vertex[i].color == vertex[current].color)
						{	
							Answer = -1;
							break;
						}
					}
					//vertex[i].depth = vertex[current].depth + 1;
					rear -> next = ( struct queue *) malloc( sizeof( struct queue) );
					rear -> next -> element = &vertex[ i];
					vertex[i].color = 1 - vertex[current].color;
					rear = rear -> next;
					rear -> next = NULL;
				}
			}
			if( Answer == -1)
				break;
			// Deleting the Parent From Queue
			struct queue *temp = front;
			front = front -> next;
			free(temp);
		}
		int count = 0;
		int display[nov];
		if( Answer == -1)
			count = -1;
		else
		{
			for( i=0; i<nov; i++)
			{
				if( vertex[i].color == 1)
				{
					display[count++] = vertex[i].data;
				}
			}
		}
		printf("#%d %d", test1, count);
		for( i=0; i<count; i++)
		{
			printf(" %d", display[i] );
		}
		printf("\n");
	}
	return 0;
}








