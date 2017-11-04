#include <stdio.h>
#include <assert.h>

#include "graph.h"

#define TEST_SIZE (37)

// Never call this
static void
matchSink(Graph g, int source, int sink, void *data)
{
    assert(data && sink == *((int *) data));
}

int main(int argc, char **argv)
{
    Graph g;
    int i;
    int j;

    g = createGraph(TEST_SIZE);

    assert(getVertexCount(g) == TEST_SIZE);

    // Check empty
    for(i = 0; i < TEST_SIZE; i++) {
        for(j = 0; j < TEST_SIZE; j++) {
            assert(hasEdge(g, i, j) == 0);
        }
    }

    // Check empty again
    for(i = 0; i < TEST_SIZE; i++) {
        assert(getOutDegree(g, i) == 0);
        foreach(g, i, matchSink, 0);
    }

    // Check edge count
    assert(getEdgeCount(g) == 0);

    // Add edge from every vertex to itself
    for(i = 0; i < TEST_SIZE; i++) {
        addEdge(g, i, i);
    }

    // Check previous step
    assert(getEdgeCount(g) == TEST_SIZE);

    for(i = 0; i < TEST_SIZE; i++) {
        for(j = 0; j < TEST_SIZE; j++) {
            assert(hasEdge(g, i, j) == (i == j));
        }
    }

    // Check again
    for(i = 0; i < TEST_SIZE; i++) {
        assert(getOutDegree(g, i) == 1);
        foreach(g, i, matchSink, &i);
    }

    print(g); 

    // Add edge between every vertex and every other vertex
    for(i = 0; i < TEST_SIZE; i++) {
        for(j = 0; j < TEST_SIZE; j++) {
            if(i != j) addEdge(g, i, j);
        }
    }

    // Check previous step
    assert(getEdgeCount(g) == TEST_SIZE * TEST_SIZE);

    for(i = 0; i < TEST_SIZE; i++) {
        assert(getOutDegree(g, i) == TEST_SIZE);
        for(j = 0; j < TEST_SIZE; j++) {
            assert(hasEdge(g, i, j) == 1);
        }
    }

    print(g);

    // Free memory
    destroyGraph(g);

    return 0;
}
