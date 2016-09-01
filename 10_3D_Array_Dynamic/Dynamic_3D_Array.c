/*
		Author	:	Tarun Jain
		Email	:	tarun.jain@iiitb.org
		Program	:	Create 3D Array Dynamically
*/

// Header Files
#include <stdio.h>
#include <stdlib.h>

// Macros
#define	EOL		printf("\n------------------------------\n");

// Main Function
int main()
{
	// Variables
	int x, y , z;
	int i, j, k;
	int ***matrix;

	// Get Dimensions
	printf("\nEnter the dimensions you want : ");
	scanf("%d %d %d", &x, &y, &z);

	EOL;
	
	// Creating 3D Array
	matrix = ( int ***) calloc ( x, sizeof( int **) );

	// Pointing to new 2D Arrays
	for( i = 0; i < x; i++)
	{
		matrix[ i ] = ( int **) calloc ( y, sizeof( int *));

		// Pointing to new 1D Arrays
		for( j = 0; j < y;  j++ )
		{
			matrix[ i][ j] = (int *) calloc( z, sizeof( int));
		}
	}
	// Read Values
	for( i = 0; i < x; i++)
	{
		for( j = 0; j < y;  j++ )
		{
			for( k = 0; k < z;  k++ )
			{
				printf("\nEnter the Element at Matrix[ %d][ %d] [ %d]  :  ", i, j , k);
				scanf("%d", &matrix[i][j][k]);
			}
		}
		EOL;
		printf("dimension changed");
		EOL;
	}
	
	printf("\nMatrix is : \n");
	EOL;
	// Display
	for( i = 0; i < x; i++)
	{
		for( j = 0; j < y;  j++ )
		{
			for( k = 0; k < z;  k++ )
			{
				printf("%d ", matrix[i][j][k]);
			}
			printf("\n");
		}
		EOL;
		printf("dimension changed");
		EOL;
	}
	printf("\n");
	
	return 0;
}
