// Chapter 4, Problem 2
// Minimal Tree
// Given a sorted (increasing order) array with unique integer elements, write
// an algorithm to create a binary search tree of minimal height.

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <assert.h>

// Binary tree node
typedef struct node {
	int value;
	struct node *left;
	struct node *right;
} Node;

// Inorder printing (scans tree from left to right)
void printTree(Node *node) {
	if(node == NULL)
		return;
	printTree(node->left);
	printf("%d ", node->value);
	printTree(node->right);
}

// Find the median value of a subsection of an ordered array, and recurse on
// the left and right halves. Return the root of the subtree.
Node *createMinTreeHelper(int array[], int start, int end) {
	int mid = start + ceil((end - start) / 2.0);
	int median = array[mid];
	// printf("Median: %d\nS: %d, M: %d, E: %d\n", median, start, mid, end);
	Node *node = malloc(sizeof(Node));
	node->value = median;

	if(start < mid) {
		node->left = createMinTreeHelper(array, start, mid - 1);
	} else {
		node->left = NULL;
	}

	if(mid < end) {
		node->right = createMinTreeHelper(array, mid + 1, end);
	} else {
		node->right = NULL;
	}

	return node;
}

// Recursively create binary search tree of minimum height from an array in 
// increasing order. Must provide number of elements in the array.
Node *createMinTree(int array[], int n) {
	assert(array != NULL);
	return createMinTreeHelper(array, 0, n-1);
}

int main() {
	int array[] = {1, 2, 3, 4, 5, 6, 7, 8};
	Node *tree = createMinTree(array, 8);
	printTree(tree);
	printf("\n");
}
