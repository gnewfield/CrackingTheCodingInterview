// C implementation of a simple singly linked list
////////////////////////////////////////////////////////////////////////////////
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "linkedList.h"

// Create a linked list containing a single node
// Return a pointer to node (the head of the new list)
Node createLinkedList(int data) {
	Node head = NULL;
	add(data, &head);
	assert(head);

	return head;
}

// Creates new node containing data and adds to the front of the list
// Returns a pointer to the new head node of the list
void add(int data, Node *head) {
	Node new = malloc(sizeof(struct node));
	assert(new);

	new->data = data;
	new->next = *head;
	*head = new;
}

// Tail-recursive function that prints contents of linked list in order
void print(Node node) {
	if(node) {
		printf("%d\n", node->data);
		print(node->next);
	}
}

// Similar to print but NOT tail-recursive because a node cannot be free'd
// until you have free'd the node it points to. The function must recurse
// to the end of the list before free'ing anything
void destroy(Node node) {
	if(node) {
		destroy(node->next);
		free(node);
	}
}
