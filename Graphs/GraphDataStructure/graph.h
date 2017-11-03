// An interface to a basic directed graph data type that uses adjacency lists
// Citation: From Professor James Aspnes's CPSC 223 Notes
// (http://www.cs.yale.edu/homes/aspnes/classes/223/notes.html#graphs)

////////////////////////////////////////////////////////////////////////////////

typedef struct graph *Graph;

// Create a graph with n vertices labelled 0, 1, ... , n-1 and no edges
Graph createGraph(int n);

// Free memory used by graph
void destroyGraph(Graph graph);

// Add an edge to an existing graph
void addEdge(Graph graph, int u, int v);

// Return the number of vertices of a graph
int getVertexCount(Graph graph);

// Return the number of edges of a graph
int getEdgeCount(Graph graph);

// Return the number of out-edges of a vertex
int getOutDegree(Graph graph, int vertex);

// Return 1 if edge (u,v) exists, 0 otherwise
int hasEdge(Graph graph, int u, int v);

// Invoke f on all edges (u,v) with source u, supplying data as final parameter to f
void foreach(Graph graph, int u, void (*f)(Graph graph, int u, int v, void *data), void *data);
