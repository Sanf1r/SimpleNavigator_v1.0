# SimpleNavigator_v1.0

Implementation of the Simple Navigator project.

Tested on MacOS Ventura 13.6.4.

Made on November 22 2023 as part of my education in School 21 :)

# Information

This project implement several basic algorithms on graphs. Graphs are one of the basic data structures in programming that are used everywhere. Graphs can be used, for example, to interpret road maps, electrical circuits, geographic maps, for communication between people in social networks, and many other things.

* The class `Graph` contain the following public methods:
    + `LoadGraphFromFile(string filename)` - loading a graph from a file in the adjacency matrix format
    + `ExportGraphToDot(string filename)`- exporting a graph to a dot file (see materials)

* The class ` GraphAlgorithms ` contain the following public methods:
    + `DepthFirstSearch(Graph &graph, int start_vertex)` - a *non-recursive* depth-first search in the graph from a given vertex. The function  return an array that contains the traversed vertices in the order they were traversed.
    + `BreadthFirstSearch(Graph &graph, int start_vertex)` - breadth-first search in the graph from a given vertex. The function return an array that contains the traversed vertices in the order they were traversed.
    + `GetShortestPathBetweenVertices(Graph &graph, int vertex1, int vertex2)` - searching for the shortest path between two vertices in a graph using *Dijkstra's algorithm*. The function accepts as input the numbers of two vertices and returns a numerical result equal to the smallest distance between them.
    + `GetShortestPathsBetweenAllVertices(Graph &graph)` - searching for the shortest paths between all pairs of vertices in a graph using the *Floyd-Warshall algorithm*. As a result, the function returns the matrix of the shortest paths between all vertices of the graph.
    + `GetLeastSpanningTree(Graph &graph)` - searching for the minimal spanning tree in a graph using *Prim's algorithm*. As a result, the function return the adjacency matrix for the minimal spanning tree.
   + `SolveTravelingSalesmanProblem(Graph &graph)` - solving the traveling salesman's problem using the *ant colony algorithm*.

* The console interface provide the following functionality:
    1. Loading the original graph from a file
    2. Graph traversal in breadth with output of the result to the console   
    3. Graph traversal in depth with output of the result to the console
    4. Searching for the shortest path between any two vertices and displaying the result to the console
    5. Searching for the shortest paths between all pairs of vertices in the graph with the output of the resulting matrix to the console
    6. Searching for the minimal spanning tree in the graph with the output of the resulting adjacency matrix to the console
    7. Solving the salesman problem with the output of the resulting route and its length to the console

# Usage

Build with **make** command and you got SimpleNAvigator executable file with console interface :)
