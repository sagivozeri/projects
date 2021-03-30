#include <stdio.h>
#include <stdlib.h>

typedef struct _list {
	int data;
	struct _list *next;
} list;

enum failure_type {
	TYPE_BAD_INPUT,
	TYPE_NO_ELEM,
	TYPE_ALLOC_FAILED,
};

void print_failure(enum failure_type type)
{
	switch (type) {
		case TYPE_BAD_INPUT:
			printf("Error - bad input\n");
			break;
		case TYPE_NO_ELEM:
			printf("Error - no such element\n");
			break;
		case TYPE_ALLOC_FAILED:
			printf("Error - allocation failed\n");
			break;
		default:
			printf("Wrong type\n");
	}
}

void list_add(list **head, int data) {
	list *curr, *elem;

	if (!head) {
		print_failure(TYPE_BAD_INPUT);
		return;
	}

	curr = *head;
	elem = (list*)malloc(sizeof(*head));
	if (!elem) {
		print_failure(TYPE_ALLOC_FAILED);
		return;
	}

	elem->data = data;
	elem->next = NULL;

	if (!curr) {
		*head = elem;
		return;
	}

	while (curr->next)
		curr = curr->next;


	curr->next = elem;
}

void list_print(list *head)
{
	if (!head)
		printf("List is empty");

	while (head) {
		printf("%d ", head->data);
		head = head->next;
	}

	printf("\n\n");
}

void list_free(list **head)
{
	list *curr, *tmp;

	if (!head)
		return;

	curr = *head;

	while (curr) {
		tmp = curr;
		curr = curr->next;
		free(tmp);
	}

	*head = NULL;
}

int list_get_length(list *head)
{
	int num = 0;

	while (head) {
		num++;
		head = head->next;
	}

	return num;
}

int list_get_node(list *head, int num)
{
	if (!head)
		return 0xFFFFFFFF;

	while (head && num) {
		num--;
		head = head->next;
	}

	if (head)
		return head->data;
}

#if 0
list* _list_reverse(list *curr, list *next)
{
	list *tmp;

	if (!next)
		return curr;

	tmp = next->next;

	next->next = curr;

	return _list_reverse(next, tmp);
}

void list_reverse(list **head)
{
	if (!head || !(*head))
		return;

	*head = _list_reverse(NULL, *head);
}
#elif 0
void list_reverse(list **head)
{
	list *prev, *curr, *next;

	if (!head || !(*head))
		return;

	prev = NULL;
	curr = *head;
	next = curr->next;

	while (next) {
		curr->next = prev;
		prev = curr;
		curr = next;
		next = next->next;
	}

	curr->next = prev;

	*head = curr;
}
#else
list *_list_reverse(list *prev, list *curr)
{
	list *next;

	if (!curr)
		return prev;

	next = curr->next;
	curr->next = prev;

	return _list_reverse(curr, next);
}

void list_reverse(list **head)
{
	if (!head || !(*head))
		return;

	*head = _list_reverse(NULL, *head);
}
#endif

int main()
{
	list *head = NULL, *new_list = NULL;
	int len, d;

	while (1) {
		printf("add number to list:\n");
		scanf("%d", &d);
		if (d == -1)
			break;

		list_add(&head, d);
	}

	printf("The list is:\n");
	list_print(head);

	list_reverse(&head);
	printf("The list reversed is:\n");
	list_print(head);

	printf("List length: ");
	len = list_get_length(head);
	printf("%d\n", len);

	if (len)
		printf("The middle node is: %d\n", list_get_node(head, len/2));
	else
		printf("No middle node - list is empty\n");

	list_free(&head);

	return 0;
}
