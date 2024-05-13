# Graph-Algorithm

This is the prompt given for the programming assignment given in class:
1)	[Part One] Design an interface for the user to provide information about nodes and edges for an undirected graph; according to the user input, display the adjacency matrix and adjacency list of the graph.
2)	[Part Two] Ask the user to specify the source node s and then run BFS on your graph; output all tracking tables (as discussed in class) as well as the queue contents.


This is how the assignment is ran:
The program first asks you to input the number of vertices and edges in your graph, then it displays the adjacency matrix and adjacency list of the graph. It then asks for a source vertex character to start BFS from. The BFS algorithm will run from the source vertex that was specified, and it will display the current state of the BFS queue, colors, distances, and predecessors at each step until all vertices reachable from the source are visited. After the BFS is completed, it will tell you if there are any vertices not connected to the source.
