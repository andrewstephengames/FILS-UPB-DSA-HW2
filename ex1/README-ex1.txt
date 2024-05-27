Exercise 1 - Network of Devices

We have the class "Graph, which created the graph itslef using the atrix of adjicency method, including a constructor and functions to add nodes, vertexes and info on them

Declaration of:

	-"N", as the number of devices, globally declared to be seen by all functions
	-graph "network", ith 100 possible nodes
	-"u" and "v", being written from a text file, as the incident nodes
	-"countInput", used to count the number of inputs from file, for easier error handle
	-"maxInput", to calculate the maximum number of inputs possible for any graph(number of verteces for any complete graph with "N" nodes)
	-"isNetworkConnected", which takes the value of the "connected" function
	
Functions:

	-"bfs", "dfs", "unvisit", used for traversing the graph, thought we might need them, but we do not
	-"isCompleteGraph", which checks if the graph is complete or not
	-"isNodeIsolated", which checks if a node is isolated or not
	-"isCircuitEulerian", which checks if we have an eulerian curcuit inside the graph or not
	-"connected", which uses all the functions from above(except the first 3 ones), and checks if we have a connected network or not

Errors:

	-node is incident to itself
	-node is out of the possible range (0 < u,v < N)
	-too many imputs
	-input writtent more than once in the list

User instructions:

-the user will firts think of the number of devices he wants to have
-then, they will insert inside the "inputList.txt" text file the list of connections, in the following form:

node1 node2
node2 node3
..........

-after running the code, the user must input the actual number of devices, the one he thought in the first step, and there will be a message displayed regarding the cnectivity of the graph, or an error message, if there is any error in the list of inputs