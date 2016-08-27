/*
	Author	:	Tarun Jain
	Roll No	:	MT2015120
	Program	:	Recursive Program to find all Permutation if 'n' numbers and 'r' places is given.
	Date 	:	10-Aug-2016
*/

// Header Files
#include <stdio.h>
#include <stdlib.h>

// Function Prototype
void permutation( int num, int places, int arr[], int sum);

// Main Function
int main()
{
	// Variables
	int i, num, places, noOfTestCases;
	int *arr;

	// Input Variables
	scanf( "%d" , &noOfTestCases);

	// Run Code for noOfTestCases times
	while( noOfTestCases--)
	{
		// Read Input from User
		scanf( "%d" , &num);
		scanf( "%d" , &places);
		if( num < places)
		{
		    printf("Invalid Operations...");
		    continue;
		}

		// Get Memory for Storing Numbers
		arr = (int *) malloc ( num * sizeof(int));

		// Store Numbers
		for( i = 0; i < num ; i++)
		{
			arr[i] = i+1;
		}

		// Find All Permutations
		permutation( num, places, arr, 0 );

		// Free Up the Memory
		free(arr);
	}
	return 0;
}

// Permutation Function
void permutation( int num, int places, int arr[], int sum)
{
	// Variables
	int i, j,k;
	int *temp;
    	int total = sum;

	// If places exists
	if( places)
	{
		for( i = 0; i < num ; i++)
		{

			// Building Permutation in process
			sum = total * 10 + arr[i];

			// Getting Memory for new array
			temp = ( int *) malloc ( (num-1) * sizeof(int));

			// Store Numbers other than current
			for( j = 0, k = 0; j < (num-1) ; k++)
			{
				// If Current Number - Skip
				if( k == i)
					continue;

				// Copy the Other Numbers
				else
				{
					temp[j] = arr[k];
					j++;
				}

			}

			// Recursive Call
			permutation( num-1, places -1, temp, sum);

			// Free Up the Memory
			free(temp);
		}
	}
	// If Permutation Completed - Print it
	else
	{
		printf("%d\n", sum);
	}
}


