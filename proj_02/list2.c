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

void list_add(list **head, int data)
{
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

int sum_lists(list *head1, list *head2, list **sum)
{
	int d1 = 0, d2 = 0, val = 0, div = 0, rem = 0;

	while (head1 || head2) {
		if (head1) {
			d1 = head1->data;
			head1 = head1->next;
		}

		if (head2) {
			d2 = head2->data;
			head2 = head2->next;
		}

		val = d1 + d2 + rem;
		div = val % 10;
		rem = val / 10;

		list_add(sum, div);
		d1 = d2 = 0;
	}
}

void reverse_list(list **head)
{
	list *prev, *curr, *next;

	if (!head || !(*head))
		return;

	prev = NULL;
	curr = *head;
	next = curr->next;

	while (curr) {
		curr->next = prev;
		prev = curr;
		curr = next;
		if (next)
			next = next->next;
	}

	*head = prev;
}

int main()
{
	list *head1 = NULL, *head2 = NULL, *sum = NULL;
	int num, d;

	while (1) {
		printf("add number to list1:\n");
		scanf("%d", &d);
		if (d == -1)
			break;

		list_add(&head1, d);
	}

	while (1) {
		printf("add number to list2:\n");
		scanf("%d", &d);
		if (d == -1)
			break;

		list_add(&head2, d);
	}

	printf("list 1 is:\n");
	list_print(head1);

	printf("list 2 is:\n");
	list_print(head2);

	reverse_list(&head1);
	reverse_list(&head2);
	sum_lists(head1, head2, &sum);
	reverse_list(&sum);

	printf("list1 + list2:\n");
	list_print(sum);

	list_free(&head1);
	list_free(&head2);
	list_free(&sum);

	return 0;
}
