#ifndef __LINKED_NLIST__
#define __LINKED_LIST__

typedef struct node_s
{
	void* data;
	int key;
	struct node_s* next;
	struct node_s* prev;
}Node;

Node* create(int new_data, int new_priority);
Node* push(Node* head, Node** tail, void* data, int key);
Node* dequeue(Node** tail);
Node* deq(Node** head);
int count(Node* head);
void traverse(Node* head);
Node* remove_max(Node* head);
Node* peek_max(Node* head);





#endif // !__LINKED_LIST__

