#include <stdio.h>
#include <stdlib.h>

struct list {
	int data;
	struct list *next;
};

void list_add(struct list **head, int data)
{
	struct list *curr, *elem;

	if (!head) return;

	elem = (struct list *)malloc(sizeof(*elem));
	if (!elem) return;

	elem->data = data;
	elem->next = NULL;

	curr = *head;

	if (!curr) {
		*head = elem;
		return;
	}

	while (curr->next)
		curr = curr->next;

	curr->next = elem;
}

void list_reverse(struct list **head)
{
	struct list *prev, *curr, *next;

	if (!head || !(*head)) return;

	prev = NULL;
	curr = *head;

	while (curr) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}

	*head = prev;
}

int delete_nth_elem(struct list **head, int n)
{
	struct list *curr, *prev;
	int data;

	if (!head || !(*head) || n < 1) return -1;

	prev = NULL;
	curr = *head;

	while (curr) {
		if (--n == 0) {
			if (!prev)
				*head = curr->next;
			else
				prev->next = curr->next;
			
			data = curr->data;
			free(curr);
			return data;
		}

		prev = curr;
		curr = curr->next;
	}

	return -1;
}

void list_print(struct list *head)
{
	if (!head)
		printf("List is empty\n");

	while (head) {
		printf("%d ", head->data);
		head = head->next;
	}

	printf("\n");
}

void list_free(struct list *head)
{
	struct list *tmp;

	while (head) {
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

int main()
{
	struct list *head = NULL;
	int data, n;

	while (1) {
		printf("Enter a number to add to the list:\n");
		scanf("%d", &data);
		if (data < 0)
			break;

		list_add(&head, data);
	}

	list_print(head);
	list_reverse(&head);
	list_print(head);
	
	printf("Print number of element to delete\n");
	scanf("%d", &n);
	data = delete_nth_elem(&head, n);
	if (data >= 0)
		printf("Element value is %d\n", data);

	list_print(head);
	list_free(head);

	return 0;
}
