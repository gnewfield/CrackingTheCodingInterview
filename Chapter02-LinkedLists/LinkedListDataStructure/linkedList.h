// An interface to a basic linked list data structure implemented in C
////////////////////////////////////////////////////////////////////////////////

typedef struct node {
	int data;
	struct node *next;
} *Node;

// Create linked list consisting of a single node
// Returns pointer to new head of linked list
Node createLinkedList(int data);

// Create new node and insert at front of the list
// Modify head pointer to point at new head
void add(int data, Node *head);

// Print contents of list, beginning with head
void print(Node head);

// Free space occupied by linked list
void destroy(Node head);
