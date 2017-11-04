// Test of linked list implementation
////////////////////////////////////////////////////////////////////////////////
#include <assert.h>

#include "linkedList.h"

int main() {
	Node head = createLinkedList(4);
	add(3, &head);
	add(2, &head);
	add(1, &head);
	add(0, &head);

	print(head);

	destroy(head);
	//assert(!head);

	return 0;
}
