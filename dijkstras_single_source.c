/*
	Author		:		Tarun Jain
	Roll No.		:		MT2015120
	College		: 		IIITB
	Email		:		Tarun.Jain@iiitb.org
	Program 	:		Dijkstra's Single Source Shortest Path ( For Each Node ) - Min Heap Used
	Assumption	:		None
*/

// Header Files
#include <stdio.h>
#include <stdlib.h>
// Structures

// Macros and Global Variables

// Function Prototypes
void readGraph( int *, int *, int *, int *, int ***);
void printGraph( int , int***);

// Main Function
int main()
{
	// Variables
	int nNodes, nEdges, isDirected, source;
	int **graph_data;

	// Read Graph Data
	readGraph( &nNodes, &nEdges, &isDirected, &source, &graph_data);

	// Printing Graph Data
	printf("\n\nInputted Graph is : \n");
	printGraph( nNodes, &graph_data);
	
	free(graph_data);
	return 0;
}

// Read Graph Data
void readGraph( int *nNodes1, int *nEdges1, int *isDirected1, int *source1, int ***graph_data1)
{
	// Variables
	int nNodes, nEdges, isDirected, source;
	int i, j ;
	
	// Nodes
	printf( "\nEnter No. of Nodes in Graph : ");
	scanf( "%d", &nNodes);

	// Edges
	do
	{
		printf( "\nEnter No. of Edges in Graph : ");
		scanf( "%d", &nEdges);
		if( nEdges < nNodes -1)
			printf("\nGraph Seems to be Disconnected.\nNo. of Edges should be atleast %d. Retry ...\n", nNodes-1);
	} while ( nEdges < nNodes -1);

	// Directed or Undirected
	do
	{
		printf( "\nIs Graph Directed ? \t\tPress 0 if No, Press 1 if Yes : ");
		scanf( "%d", &isDirected);
		if( isDirected != 0 && isDirected != 1)
			printf( "\nWrong Input. Retry ...\n" );
	} while ( isDirected != 0 && isDirected != 1);

	// Creating 2D Array in Heap Memory
	int **graph_data = ( int **) calloc ( nNodes , sizeof( int *) );
	for( i = 0; i < nNodes; i++)
	{
		graph_data[i] = ( int *) calloc ( nNodes , sizeof(int));
	}
	
	// Edge Data
	for( i =0; i < nEdges; i++)
	{
		int x, y;
		printf("\nEnter Data for Edge No.  %d \n", i+1);
		do
		{
			printf("\nEnter Source for Edge No. %d : ", i+1);
			scanf("%d", &x);
			printf("\nEnter Destination for Edge No. %d : ", i+1);
			scanf("%d", &y);
			if( (x < 1 || x > nNodes) || ( y < 1 || y > nNodes) )
			{
				printf( "\nInvalid Source or Destination in Edge No. %d. Retry ...\n", i+1);
				//continue;
			}
			else
			{	
				printf("\nEnter Weight for Edge No. %d : ", i+1);
				scanf("%d", &graph_data[x -1 ][y - 1]);
			}
		} while( (x < 1 || x > nNodes) || ( y < 1 || y > nNodes) );

		if( isDirected == 0)
			graph_data[y-1][x-1] = graph_data[x-1][y-1];	
	}

	// Source Node
	do
	{
		printf( "\nEnter Source of Graph : ");
		scanf( "%d", &source);
		if ( !( source <= nNodes && source > 0))
			printf("\nInvalid Source Node. Retry ...\n");
	} while ( !(source <= nNodes && source > 0));

	
	// Sending Values Back
	*nNodes1 = nNodes;
	*nEdges1  = nEdges;
	*isDirected1 = isDirected;
	*source1 = source;
	*graph_data1 = graph_data;
	
}

// Print Graph Function
void printGraph( int nNodes, int ***graph_data1)
{
	// Variable
	int **graph_data = *graph_data1;			// Pointer to 2D data
	int i, j;									// Loop Variables

	printf("\n\t\tColumns\t\t\n\n");
	printf("     \t");
	for( i = 0; i < nNodes; i++)
	{
		printf("%d\t", i+1);		
	}
	printf("\n");
	for( i = 0; i < nNodes; i++)
	{
		printf("\nRow %d :", i+1);
		for( j = 0; j < nNodes; j++)
		{
			printf("\t%d",graph_data[i][j] );
		}
		printf("\n");
	}
	
}

