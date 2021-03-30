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

#if 0
int delete_nth_element(list **head, int num, int *data)
{
	list *curr, *prev;

	if (!head || !(*head) || num < 0) {
		print_failure(TYPE_BAD_INPUT);
		return 1;
	}

	curr = *head;

	if (num == 0) {
		*data = curr->data;
		*head = curr->next;
		free(curr);
		return 0;
	}

	if (!curr->next) {
		print_failure(TYPE_NO_ELEM);
		return 1;
	}

	prev = curr;
	curr = curr->next;

	num--;

	while (curr) {
		if (num == 0) {
			prev->next = curr->next;
			*data = curr->data;
			free(curr);
			return 0;
		}

		prev = curr;
		curr = curr->next;
		num--;
	}

	print_failure(TYPE_NO_ELEM);
	return 1;
}
#elif 0
int delete_nth_element(list **head, int num, int *data)
{
	list *tmp1, *tmp2;

	if (!head || !(*head) || num < 0) {
		print_failure(TYPE_BAD_INPUT);
		return 1;
	}

	tmp1 = *head;

	if (!num) {
		*data = tmp1->data;
		*head = tmp1->next;
		free(tmp1);
		return 0;
	}

	while (--num && tmp1)
		tmp1 = tmp1->next;

	if (!tmp1 || !tmp1->next) {
		print_failure(TYPE_NO_ELEM);
		return 1;
	}

	*data = tmp1->data;
	tmp2 = tmp1->next;
	tmp1->next = tmp2->next;
	free(tmp2);

	return 0;
}
#elif 0
int delete_nth_element(list **head, int index, int *value)
{
	list *curr, *prev, *newhead;
	int i;

	if (!head || !*head) {
		print_failure(TYPE_BAD_INPUT);
		return -1;
	}

	prev = NULL;
	curr = *head;

	for (i = 0; curr != NULL; i++) {
		if (i == index) {
			if (!prev) {
				newhead = curr->next;
				*head = newhead;
			} else {
				prev->next = curr->next;
			}

			*value = curr->data;
			free(curr);
			return 0;
		}

		prev = curr;
		curr = curr->next;
	}

	print_failure(TYPE_NO_ELEM);
	return -1;
}
#elif 0
int delete_nth_element(list **head, int n, int *data)
{
	list *tmp, *tmp2;

	if (!head || !(*head)) {
		print_failure(TYPE_BAD_INPUT);
		return -1;
	}

	tmp = *head;

	if (n == 0) {
		*data = tmp->data;
		*head = tmp->next;
		free(tmp);
		return 0;
	}

	while (n > 1 && tmp->next) {
		n--;
		tmp = tmp->next;
	}

	if (!tmp->next) {
		print_failure(TYPE_NO_ELEM);
		return 1;
	}

	tmp2 = tmp->next;
	tmp->next = tmp2->next;
	*data = tmp2->data;
	free(tmp2);
	return 0;
}
#else
int delete_nth_element(list **head, int n, int *data)
{
	list *prev, *curr, *tmp;

	if (!head || !(*head) || n < 1) {
		print_failure(TYPE_BAD_INPUT);
		return 1;
	}

	curr = *head;
	prev = NULL;

	while (curr) {
		if (n == 1) {
			if (!prev)
				*head = curr->next;
			else
				prev->next = curr->next;

			*data = curr->data;
			free(curr);
			return 0;
		}

		prev = curr;
		curr = curr->next;
		n--;
	}

	print_failure(TYPE_NO_ELEM);

	return 1;
}
#endif

void remove_dup(list *head)
{
	list *prev, *curr = head, *runner;

	while (curr) {
		prev = curr;
		runner = curr->next;

		while(runner) {
			if (runner->data == curr->data) {
				prev->next = runner->next;
				free(runner);
				runner = prev->next;
			} else {
				prev = runner;
				runner = runner->next;
			}
		}

		curr = curr->next;
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

int main()
{
	list *head = NULL, *new_list = NULL;
	int num, d;

	while (1) {
		printf("add number to list:\n");
		scanf("%d", &d);
		if (d == -1)
			break;

		list_add(&head, d);
	}

	printf("The list is:\n");
	list_print(head);

	printf("choose an element to remove:\n");
	scanf("%d", &num);
	if (!delete_nth_element(&head, num, &d)) {
		printf("the data is %d and the new list is:\n", d);
		list_print(head);
	}

	remove_dup(head);
	printf("After removing duplicates the new list is:\n");
	list_print(head);

	list_free(&head);

	return 0;
}
