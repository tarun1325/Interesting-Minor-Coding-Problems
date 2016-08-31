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
