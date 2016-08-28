
Format of the Input file:
No. of Vertices
No. of Edges
0 -> Undirected Graph; 1 -> Directed Graph
{ Edge List with Weights of corresponding edges }
Source Vertex

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

