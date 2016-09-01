/*
		Author		:		Tarun Jain
		College		:		IIITB
		Email		:		tarun.jain@iiitb.org
		Program		:		write a program , given a matrix with 0’s and 1’s , you enter the matrix at (0,0) in left to right direction , whenever you 							encounter a 0 you retain in same direction , if you encounter a 1’s you have to change direction to right of current direction 								and change that 1 value to 0, you have to find out from which index you will leave the matrix at the end.
		Assumptions	:		MAX_SIZE is the size of Matrix allowed by this program ( 5000 x 5000 ) 
*/

// Header Files
#include <stdio.h>

// Macros
#define MAX_SIZE	50
// Main Function
int main()
{
	// Variables
	int matrix[MAX_SIZE][MAX_SIZE], no_row, no_col;
	int i, j;
	int dir = 1;										// 1 - right :: 2 - bottom :: 3 - left :: 4 - up

	// Read Number of row and column
	scanf( "%d%d", &no_row, &no_col);
	// Read Matrix
	for( i = 0; i < no_row; i++)
	{
		for( j = 0; j < no_col; j++)
			scanf("%d", &matrix[i][j]);
	}
	for( i = 0; i < no_row; i++)
	{
		for( j = 0; j < no_col; j++)
			printf("%d\t", matrix[i][j]);
		printf("\n\n");	
	}

	
	// Logic
	i = j = 0;
	while( ( i < no_row ) && ( j < no_col ) && ( j >= 0 ) && ( i >= 0 ) )
	{
		// If '1' - Switch the Direction to the Right of Current Direction
		if( matrix[ i][ j] == 1)
		{
			matrix[i][j] = 0;							// Set that Element as Zero - Also it will avoid infinite looping
			switch( dir )
			{
				case 1:	dir = 2;						// Right Direction Changed to Down Direction
						break;
				case 2:	dir = 3;						// Down Direction Changed to Left Direction
						break;
				case 3:	dir = 4 ;						// Left Direction Changed to Up Direction
						break;
				case 4:	dir = 1;						// Up Direction Changed to Left Direction
						break;
			}
		}
		// Moving in the Direction
		switch( dir )
		{
			case 1:	j++;							// Moving Right
					break;
			case 2:	i++;							// Moving Down
					break;
			case 3:	j--;							// Moving Left
					break;
			case 4:	i--;							// Moving Up
					break;
		}
	}
	// Finding Last Index
	switch( dir )
	{
		case 1:	j--;							
				break;
		case 2:	i--;							
				break;
		case 3:	j++;							
				break;
		case 4:	i++;							
				break;
	}

	// Result
	printf("\n Index at Which Matrix is left : Row :%d , Col :  %d\n", i +1 , j + 1);
	
	return 0;
}
