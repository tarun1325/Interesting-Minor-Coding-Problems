/*
		Author		:		Tarun Jain
		College		:		IIITB
		Email		:		tarun.jain@iiitb.org
		Program		:		Find the sum of all the nodes at depth 'k' of a given tree
		Input Format	:		k  Tree
							Tree is given in the format - ( root value ( left subtree) ( right subtree) )
							k = depth
							Example : Input: 2 (0(5(6()())(4()(9()())))(7(1()())(3()())))
									Output: 14
														     0
														  /     \
													       5         7
													    /    \      /   \
													   6       4    1     3
														    \
														     9 

		Logic		:	The No. of Opening Brackets is equal to one more than the depth of tree at any particular time.
*/

// Header Files
#include <stdio.h>

// Main Function
int main()
{
	// Variables
	int sum_at_depth_k = 0;
	int count_brackets = 0;
	int depth_k;
	char input;
	int temp = 0, t1;
	
	// Read Input 
	scanf("%d" , &depth_k);
	scanf("%c", &input);

	// Read Tree Data
	while( input != '\n')
	{
		// If Brackets Starts
		if( input == '(' )
		{
			count_brackets++;								// Increment Counter
			scanf("%c", &input);								// Scan Next Character
			if( input == ')')									// If Closing Brackets - NO DATA
			{
				count_brackets--;								// Decrement Counter
				scanf("%c", &input);							// Scan Next Character
				continue;									// Next Iteration
			}
			else 											// If Opening Bracket Followed by DATA
			{
				t1 = input - '0';								// Reading Data Character By Character
				while(t1>= 0 && t1 <= 9)						// Until Digit is Read
				{
					temp = (temp * 10) + ( input - '0');			// Making Integer From Characters
					scanf( "%c", &input);
					t1 = input -'0';
				};
				if( depth_k == (count_brackets-1))				// If Depth is Matched
					sum_at_depth_k += temp;					// Add to Sum
				temp = 0;									// Reset temp
				continue;									// Next Iteration
			}
		}
		else if( input == ')')									// Closing Brackets
		{
			count_brackets--;									// Decrement Counter
		}
		scanf("%c", &input);									// Scan Next Character
	}
	
	// Print Result
	printf("\n%s : Sum of Nodes at depth %d is : %d \n", __FUNCTION__, depth_k,  sum_at_depth_k );
	return 0;
}
