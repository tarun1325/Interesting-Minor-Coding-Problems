/*
	Author		:		Tarun Jain
	Roll No.		:		MT2015120
	College		: 		IIITB
	Email		:		Tarun.Jain@iiitb.org
	Program 	:		Dijkstra's Single Source Shortest Path ( For Each Node ) - Min Heap Used
	Assumption	:		Infinite Distance is Taken as 1000000 ( Maximum Weight of Edge can be 1000000 )
						Min-Heap Array Index starts at 0 (Zero).
	Observations	:		When Input File is Provided and Any Wrong Input is Provided. Then Program Keeps Giving Invalid Input Message.
						Reason: Because When it Ask to re-enter the value, it Considers the next value of any other edge as weight. So at the end Source 						Node is not Found. Try by Giving one value of any edge wait more than INFINITE value.

	Corner Case 	:		Weight is put very large than INFINITE sometimes becomes negative value due to signed representation in Computers. (Solved)
*/

// Header Files
#include <stdio.h>
#include <stdlib.h>

// Macros
#define INFINITE  1000000
#define EFO		printf("\n--------------------------------------------------------------------\n");

// Structures
struct node
{
	int data;						// Node Number
	int parent;					// Parent of Current Node
	int distance;					// Cost / Distance  from Parent
};

// Macros and Global Variables

// Function Prototypes
void readGraph( int *nNodes1, int *nEdges1, int *isDirected1 , int *source1, int ***graph_data1);
void printGraph( int nNodes, int*** graph_data1);
struct node** initDijkstras( int source, int nNodes);
void printHeap( struct node **minHeap, int nNodes);
void minHeapifyBottom( int current_index, struct node **minHeap);
void runDijkstras( struct node **minHeap, int ***graph_data1, int nNodes, int isDirected);
struct node* deleteHeap( struct node **minHeap, int *nNodes);
void minHeapifyTop( int parent_index, struct node **minHeap, int nNodes);
struct node* findNode( int data, struct node **minHeap, int nNodes);

// Main Function
int main()
{
	// Variables
	int nNodes, nEdges, isDirected, source;
	int **graph_data;
	struct node **minHeap;

	// Read Graph Data
	readGraph( &nNodes, &nEdges, &isDirected, &source, &graph_data);

	// Printing Graph Data
	printf("\n\nmain() :Inputted Graph is : \n");
	printGraph( nNodes, &graph_data);

	printf("\nmain() : Dijkstra's Single Source Shortest Path for Source Node %d\n", source);
	// Creating Nodes and Setting Initial Values
	minHeap = initDijkstras( source, nNodes);

	// Print Heap Data
	printf("\nmain() : Initial Heap State ... \n");
	printHeap( minHeap, nNodes);

	// Execute Dijkstras Algorithm on Graph
	runDijkstras( minHeap, &graph_data, nNodes, isDirected);

	EFO;
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
			printf("\nreadGraph() : Graph Seems to be Disconnected.\nNo. of Edges should be atleast %d. Retry ...\n", nNodes-1);
	} while ( nEdges < nNodes -1);

	// Directed or Undirected
	do
	{
		printf( "\nIs Graph Directed ? \t\tPress 0 if No, Press 1 if Yes : ");
		scanf( "%d", &isDirected);
		if( isDirected != 0 && isDirected != 1)
			printf( "\nreadGraph() : Wrong Input. Retry ...\n" );
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
		EFO;
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
				printf( "\nreadGraph() : Invalid Source or Destination in Edge No. %d. Retry ...\n", i+1);
				//continue;
			}
			else
			{	
				do
				{
					 graph_data[x -1 ][y - 1]  = 0;
					printf("\nEnter Weight for Edge No. %d : ", i+1);
					scanf("%d", &graph_data[x -1 ][y - 1]);
					if(( graph_data[x -1 ][y - 1] > INFINITE) ||  (graph_data[x -1 ][y - 1] < 1))
						printf( "\nreadGraph() : Maximum Allowed Weight is between 1 to %d. Retry ... \n", INFINITE);
				}while(( graph_data[x -1 ][y - 1] > INFINITE) ||  (graph_data[x -1 ][y - 1] < 1));
			}
		} while( (x < 1 || x > nNodes) || ( y < 1 || y > nNodes) );

		if( isDirected == 0)
			graph_data[y-1][x-1] = graph_data[x-1][y-1];	
		EFO;
	}

	// Source Node
	do
	{
		printf( "\n\nEnter Source of Graph : ");
		scanf( "%d", &source);
		if ( !( source <= nNodes && source > 0))
			printf("\nreadGraph() : Invalid Source Node. Retry ...\n");
	} while ( !(source <= nNodes && source > 0));

	
	// Sending Values Back
	*nNodes1 = nNodes;
	*nEdges1  = nEdges;
	*isDirected1 = isDirected;
	*source1 = source;
	*graph_data1 = graph_data;
	EFO;
}

// Print Graph Function
void printGraph( int nNodes, int ***graph_data1)
{
	// Variable
	int **graph_data = *graph_data1;			// Pointer to 2D data
	int i, j;									// Loop Variables
	EFO;

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
	EFO;
}

// Initialize Dijkstras
struct node** initDijkstras( int source, int nNodes)
{
	// Variables
	int i ;
	
	// Creating Min Heap using Array
	struct node **minHeap = (struct node **) malloc ( sizeof( struct node*) * nNodes);

	// Initialize Min Heap - Parents = NULL and Distance = INFINITE
	for( i = 0; i < nNodes; i++)
	{
		minHeap[i] = ( struct node *) calloc ( 1, sizeof(struct node));
		minHeap[i] -> data = i+1;
		minHeap[i] -> parent = 0;
		minHeap[i] -> distance = INFINITE;
	}
	// Source to Source Distance
	minHeap[ source-1 ] -> distance = 0;

	// Heapifying for Source from Bottom to Top
	minHeapifyBottom( source - 1, minHeap);

	return minHeap;
}

// Print Heap Function
void printHeap( struct node **minHeap, int nNodes)
{
	int i;
	EFO;
	printf( "\nNode\tParent\tDistance \n\n" );
	for( i = 0 ; i < nNodes; i++)
	{	
		// Parent is Null
		if( minHeap[i] -> parent == 0)
			printf("%d\tNULL\t%d\n", minHeap[i] -> data, minHeap[i] -> distance);
		else
			printf("%d\t%d\t%d\n", minHeap[i] -> data, minHeap[i] -> parent , minHeap[i] -> distance);
	}
	EFO;
}

// Min-Heapify Bottom Function - ( Bottom to Top)
void minHeapifyBottom( int current_index, struct node **minHeap)
{
	int current_distance = minHeap[ current_index] -> distance;			// Current Node's Distance
	int parent_index = (current_index - 1) / 2;						// Finding Parent Index
	int parent_distance = minHeap[ parent_index] -> distance;			// Parent Node's Distance
	struct node *temp = NULL;	
	while( (current_distance < parent_distance)  && (!( parent_index < 0 )) )	// If Child Distance is Minimum then Parent's Distance
	{
		// Swap Parent and Current Nodes
		temp = minHeap[ current_index];
		minHeap[ current_index] = minHeap[ parent_index];
		minHeap[ parent_index] = temp;

		// Update Current Node and Parent Node
		current_index = parent_index;
		current_distance = parent_distance;
		parent_index = ( current_index - 1 ) / 2;
		parent_distance = minHeap[ parent_index ] -> distance;
	}
}
// Run Dijkstras Function
void runDijkstras( struct node **minHeap, int ***graph_data1, int nNodes, int isDirected)
{
	int result[ nNodes][3];
	int j, n= nNodes;
	int k;
	int **graph_data = *graph_data1;
	struct node *deleted;
	while( n > 0)
	{
		deleted = deleteHeap( minHeap, &n);
		printf("\nrunDijkstras() : Deleted Node : %d , Distance : %d , Parent : %d\n", deleted -> data, deleted -> distance, deleted -> parent );
		result [ nNodes - n - 1][0] = deleted -> data;
		result [ nNodes - n - 1][1] = deleted -> distance;
		result [ nNodes - n - 1][2] = deleted -> parent;
		
		deleted -> distance = INFINITE;
		minHeapifyTop( 0, minHeap, n);
		
		for( j=0; j < nNodes;  j++)
		{
			int new_weight = graph_data[ deleted -> data - 1][  j ] ;
			if(  new_weight  != 0 )								// Edge Exist
			{
				struct node * temp = findNode( j+1, minHeap, n );
				for( k =0; k < n; k++)
				{
					if( temp == minHeap[k])
						break;
				}
				if( temp != NULL)
				{
					if( new_weight <= temp -> distance)
					{
						temp -> distance = new_weight;
						temp -> parent = deleted -> data;
						printf("");
						minHeapifyBottom(  k, minHeap);
					}
				}
				graph_data[ deleted -> data -1 ][ j] = 0;
				if( isDirected == 0)
					graph_data[ j][ deleted ->data -1] = 0;
			}
		}
		printf("\nHeap Status After Smallest Node Deleting and Updating Other Neighbours\n");
		printHeap( minHeap, n);
	}
	EFO;
	printf("\n\nSingle Source Shortest Path Generated By Dijkstra's Algorithm is:\n");
	printf("\nNode\t\tParent\t\tDistance From Parent\n");
	for( k =0; k < nNodes; k++)
	{
		printf("%d\t\t%d\t\t%d\n", result[k][0], result[k][1], result[k][2]);		
	}
}

// Find Node with Given Data
struct node* findNode( int data, struct node **minHeap, int nNodes)
{
	int i;
	for( i = 0; i < nNodes; i++)
	{
		if( data == minHeap[i] -> data )
			return minHeap[i];
	}
	return NULL;
}
// Delete Heap Function
struct node* deleteHeap( struct node **minHeap, int *nNodes)
{
	struct node *temp;
	// Swap 0th index and (n-1)th index
	temp = minHeap[ *nNodes -1];
	minHeap[ *nNodes -1] = minHeap[ 0];
	minHeap[0] = temp;
	(*nNodes)--;
	return minHeap[ *nNodes ];
}

// Min Heapify Top Function
void minHeapifyTop( int parent_index, struct node **minHeap, int nNodes)
{
	int child1_index = (parent_index * 2 ) + 1;
	int child2_index = (parent_index * 2 ) + 2;
	int child1_distance = minHeap[ child1_index] -> distance;
	int child2_distance = minHeap[ child2_index] -> distance;
	int parent_distance = minHeap[ parent_index] -> distance;
	struct node *temp;
	
	while(( ( parent_distance > child1_distance ) || ( parent_distance > child2_distance )) && (child1_index < nNodes && child2_index < nNodes) )
	{
		if( ( parent_distance > child1_distance ) && ( parent_distance > child2_distance ))
		{
			if( child1_distance > child2_distance && (child1_index < nNodes && child2_index < nNodes))
			{
				// Swap Parent with Child2
				temp = minHeap[ child2_index];
				minHeap[ child2_index] = minHeap[ parent_index];
				minHeap[ parent_index] = temp;

				parent_index  = child2_index;
			}
			else if( child1_distance < child2_distance && (child1_index < nNodes && child2_index < nNodes)) 
			{
				// Swap Parent with Child1
				temp = minHeap[ child1_index];
				minHeap[ child1_index] = minHeap[ parent_index];
				minHeap[ parent_index] = temp;

				parent_index  = child1_index;
			}
		}
		else if ( parent_distance > child2_distance && child2_index < nNodes )
		{
			// Swap Parent with Child2
			temp = minHeap[ child2_index];
			minHeap[ child2_index] = minHeap[ parent_index];
			minHeap[ parent_index] = temp;

			parent_index  = child2_index;
		}
		else if ( parent_distance > child1_distance && child1_index < nNodes )
		{
			// Swap Parent with Child1
			temp = minHeap[ child1_index];
			minHeap[ child1_index] = minHeap[ parent_index];
			minHeap[ parent_index] = temp;

			parent_index  = child1_index;
		}
		child1_index = (parent_index * 2) + 1;
		child2_index = (parent_index * 2) + 2;
	}
} 

