// Implementation of a basic directed graph data type that uses adjacency lists
// (represented as variable-length arrays)
// Citation: From Professor James Aspnes's CPSC 223 Notes
// (http://www.cs.yale.edu/homes/aspnes/classes/223/notes.html#graphs)

////////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <assert.h>

#include "graph.h"

typedef struct node {
	int d; // Number of nodes
	int len; // Number of slots in array
	int isSorted; // 1 if list is already sorted, 0 otherwise
	int list[]; // Actual list of successor nodes
} *Node;

struct graph {
	int n; // Number of vertices
	int m; // Number of edges
	Node alist[]; // Adjacency list (array of Node ptrs)
};

// Create a graph with n vertices labelled 0, 1, ... , n-1 and no edges
Graph createGraph(int n) {
	Graph g;
	int i;

	g = malloc(sizeof(struct graph) + sizeof(Node) * n);
	assert(g);

	g->n = n; // n vertices
	g->m = 0; // 0 edges

	// Init vertices (nodes)
	for(int v = 0; v < n; v++) {
		g->alist[v] = malloc(sizeof(struct node));
		assert(g->alist[v]);

		g->alist[v]->d = 0;
		g->alist[v]->len = 0;
		g->alist[v]->isSorted = 1;
	}

	return g;
}

void destroyGraph(Graph g) {
	for(int v = 0; v < g->n; v++) free(g->alist[v]);
	free(g);
}

void addEdge(Graph g, int source, int sink) {
	assert(source >= 0);
	assert(source < g->n);
	assert(sink >= 0);
	assert(sink < g->n);

	Node u = g->alist[source];

	// Do we need to grow vertex u's list of successors
	if(u->d == u->len) { // List is full
		u->len = u->len * 2 + 1; // + 1 neccessary for when len is 0
		u = realloc(u, sizeof(struct node) + sizeof(int) * u->len);
	}

	u->list[u->d++] = sink;
	u->isSorted = 0;

	g->alist[source] = u;

	g->m++;
}

// Return the number of vertices in the graph
int getVertexCount(Graph g)
{
    return g->n;
}

// Return the number of vertices in the graph
int getEdgeCount(Graph g)
{
    return g->m;
}

// Return the out-degree of a vertex
int getOutDegree(Graph g, int source)
{
    assert(source >= 0);
    assert(source < g->n);

    return g->alist[source]->d;
}

// When we are willing to use binary search
#define BSEARCH_THRESHOLD (10)

// Integer comparator function for sorting. Must take as input two args
// of type (void *). These must then be cast to (int *) and dereferenced
// to access value. Subtracting a from b will result in the larger of the 
// two being place first in the sorted list. This is because a negative value,
// indicates that the sort function should place a before b, a positive value,
// indicates that the sort function should place b before a, and a value of 0
// indicates that the two are equal (and the order does not matter)
static int intcmp(const void *a, const void *b)
{
    return *((const int *) a) - *((const int *) b);
}

// Return 1 if edge (source, sink) exists, 0 otherwise
int hasEdge(Graph g, int source, int sink) {
	assert(source >= 0);
	assert(source < g->n);
	assert(sink >= 0);
	assert(sink < g->n);

	Node u = g->alist[source];

	if(getOutDegree(g, source) >= BSEARCH_THRESHOLD) {
		// Make sure it is sorted
		if(!u->isSorted) {
			// Use qsort function from stdlib to sort list
			// Input: Ptr to first element in the array to be sorted, num elements
			// in the array, size in bytes of each elt, ptr to comparison function
			qsort(u->list, u->d, sizeof(int), intcmp);
		}

		// bsearch, like qsort, is a function of stdlib and has the same parameters, except
		// for one addition: the first argument must be a ptr to the target of the search
		// Returns ptr to value if found, NULL otherwise
		return bsearch(&sink, u->list, u->d, sizeof(int), intcmp) != NULL;
	} else { // Perform a simple linear search
		for(int v = 0; v < u->d; v++) {
            if(u->list[v] == sink) return 1; // Found
        }
        // Else not found
        return 0;
	}
}

void foreach(Graph g, int source, void (*f)(Graph g, int source, int sink, void *data), void *data) {
	assert(source >= 0);
    assert(source < g->n);

    Node u = g->alist[source];

    for(int v = 0; v < u->d; v++) {
        f(g, source, u->list[v], data);
    }
}
