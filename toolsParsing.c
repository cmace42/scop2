#include "scop.h"

void push(t_listParsing** head_ref, GLfloat new_number)
{
	/* 1. allocate node */
	t_listParsing* new_node
		= (t_listParsing*)malloc(sizeof(t_listParsing));
 
	/* 2. put in the number  */
	new_node->number = new_number;
 
	/* 3. Make next of new node as head and previous as NULL
	 */
	new_node->next = (*head_ref);
	new_node->prev = NULL;
 
	/* 4. change prev of head node to new node */
	if ((*head_ref) != NULL)
		(*head_ref)->prev = new_node;
 
	/* 5. move the head to point to the new node */
	(*head_ref) = new_node;
}

void insertAfter(t_listParsing *prev_node, GLfloat new_number)
{
	/*1. check if the given prev_node is NULL */
	if (prev_node == NULL) {
		printf("the given previous node cannot be NULL");
		return;
	}
 
	/* 2. allocate new node */
	t_listParsing* new_node
		= (t_listParsing*)malloc(sizeof(t_listParsing));
 
	/* 3. put in the number  */
	new_node->number = new_number;
 
	/* 4. Make next of new node as next of prev_node */
	new_node->next = prev_node->next;
 
	/* 5. Make the next of prev_node as new_node */
	prev_node->next = new_node;
 
	/* 6. Make prev_node as previous of new_node */
	new_node->prev = prev_node;
 
	/* 7. Change previous of new_node's next node */
	if (new_node->next != NULL)
		new_node->next->prev = new_node;
}

void append(t_listParsing** head_ref, GLfloat new_number)
{
	/* 1. allocate node */
	t_listParsing* new_node
		= (t_listParsing*)malloc(sizeof(t_listParsing));
 
	t_listParsing* last = *head_ref; /* used in step 5*/
 
	/* 2. put in the number  */
	new_node->number = new_number;
 
	/* 3. This new node is going to be the last node, so
		  make next of it as NULL*/
	new_node->next = NULL;
 
	/* 4. If the Linked List is empty, then make the new
		  node as head */
	if (*head_ref == NULL) {
		new_node->prev = NULL;
		*head_ref = new_node;
		return;
	}
 
	/* 5. Else traverse till the last node */
	while (last->next != NULL)
		last = last->next;
 
	/* 6. Change the next of last node */
	last->next = new_node;
 
	/* 7. Make last node as previous of new node */
	new_node->prev = last;
 
	return;
}

void printList(t_listParsing* node)
{
	t_listParsing* last;
	printf("\nTraversal in forward direction \n");
	while (node != NULL) {
		printf(" %f\n", node->number);
		last = node;
		node = node->next;
	}
}

void printListR(t_listParsing* node)
{
	t_listParsing* last; 
	printf("\nTraversal in reverse direction \n");
	while (last != NULL) {
		printf(" %f \n", last->number);
		last = last->prev;
	}
}

void freeList(t_listParsing **head_ref)
{
	t_listParsing* node = *head_ref;
	t_listParsing* tmp;

	while (node != NULL)
	{
		tmp = node->next;
		free(node);
		node = tmp;
	}
}