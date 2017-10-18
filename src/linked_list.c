#include <SDL.h>
#include <stdio.h>
#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "simple_logger.h"
#include "linked_list.h"

Node* create(int new_data, int new_key)
{
	Node* new_node = (Node*)malloc(sizeof(Node));
	memset(new_node, 0, sizeof(Node));
	new_node->data = new_data;
	new_node->key = new_key;
	new_node->next = NULL;
	new_node->prev = NULL;
	return new_node;
}

Node* push(Node* head, Node** tail, void* data, int key)
{
	Node* this_node = create(data, key); // create new node
	if(head)// if head points to not null, the head nodes prev points to this node
	{
		head->prev = this_node;
	}
	this_node->next = head; // set next to the node head points to
	head = this_node; // set head to point to this node
	if (*tail == NULL) // if tail is null, this is first node, set it to this node 
	{
		*tail = this_node;
	}

	//prev is set to NULL be default
	//slog("\n Success! Next's prev %p, Node %p, Next %p", this_node->next ? this_node->next->prev : 0, this_node, this_node->next);
	return head;
}

Node* deq(Node** head)
{
	Node* cursor = (*head);
	if (cursor == NULL)
	{
		return;
	}
	
	while (cursor->next != NULL)
	{
		cursor = cursor->next;
	}

	if (cursor->prev != NULL)
	{
		cursor->prev->next = NULL;
		return cursor;
	}
	else
	{
		*head = NULL;
		return cursor;
	}
}

Node* dequeue(Node** tail)
{
	Node* removed = (*tail);
	Node* second_to_last = (*tail)->prev;
	(*tail) = second_to_last;
	(*tail)->next = NULL;
	//
	("\n Node at %p removed. Removed node's Next %p, Previous %p", removed, removed->next, removed->prev);
	return removed;
}

int count(Node* head)
{
	Node* cursor = head;
	int c = 0;
	while (cursor != NULL)
	{
		c++;
		cursor = cursor->next;
	}
	slog("Number of elements in list: %i", c);
	return c;
}

void traverse(Node* head)
{
	Node* cursor = head;
	while (cursor != NULL)
	{
		slog("\n Node: %p Key:%i", cursor, cursor->key);
		cursor = cursor->next;
	}
}

Node* peek_max(Node* head)
{
	Node* cursor = head;
	Node* max_ptr = head;

	int max_value = NULL;
	max_value = cursor->key;

	while (cursor != NULL)
	{
		slog("max value is %i, key at cursor is %i", max_value, cursor->key);
		if (cursor->key > max_value)
		{
			max_ptr = cursor;
			max_value = max_ptr->key;
			slog("switched");
		}
		cursor = cursor->next;
	}

	slog("max val at end %i, cursor at %p, max ptr at %p", max_value, cursor, max_ptr);

	return max_ptr;
}

Node* remove_max(Node* head)
{
	Node* cursor = head;
	Node* max_ptr = head;
	int max_value = NULL;

	max_value = max_ptr->key;

	while (cursor != NULL)
	{
		//slog("max value is %i, key at cursor is %i", max_value, cursor->key);
		if (cursor->key > max_value)
		{
			max_ptr = cursor;
			max_value = max_ptr->key;
			//slog("switched");
		}
		cursor = cursor->next;
	}
	if (max_ptr->next)
	{
		max_ptr->next->prev = max_ptr->prev;
	}
	
	if (max_ptr->prev)
	{
		max_ptr->prev->next = max_ptr->next; //null ptr?
	}
	if (max_ptr == head)
	{
		head = max_ptr->next;
	}

	slog("Removed node %p with key of %i", max_ptr, max_ptr->key);

	return max_ptr;
}