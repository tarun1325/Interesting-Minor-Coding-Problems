/*
	I have modified online available code to find all combinations.
	Program : If given 'n' and 'r', Find all the nPr and print those combination
*/

#include<stdio.h>
#include<stdlib.h>

static int totalPermutations = 0;

void printArray(int arr[], int size)
{
	int count=0, i, j;
	for(i=0;i<size;i++)
	{
		for(j=i+1;j<size;j++)
		{
			if(arr[i]==arr[j])
			{
				count = 1;
				break;
			}
		}
		if( count == 1)
			break;
	}
	
	if(count == 0)
	{
	    totalPermutations++;
	    for(i = 0; i < size; i++)
	    {
			printf("%d ", arr[i]);
	    }
	    printf("\n");
	}	
	return;
}
int getSuccessor(int arr[], int k, int n)
{
	int i;
	int p = k - 1;
	while (arr[p] == n)
		p--;
		
	if (p < 0)
		return 0;

	arr[p] = arr[p] + 1;

	for(i = p + 1; i < k; i++)
		arr[i] = 1;

	return 1;
}
void printSequences(int n, int k)
{
	int i;
	int *arr = (int *) malloc ( k * sizeof(int));

	for(i = 0; i < k; i++)
		arr[i] = 1;

	while(1)
	{
			printArray(arr, k);
			if(getSuccessor(arr, k, n) == 0)
				break;
	}
	
	printf("\nTotal Permutations : %d\n", totalPermutations);
	free(arr); // free dynamically allocated array
	return;
}
int main()
{
		int num , places;
		scanf( "%d" , &num);
		scanf( "%d" , &places);
		printSequences(num, places);
		return 0;
}
