#include <stdio.h>
#include <stdlib.h>

#define INVALID_DATA 0xffffffff

struct list
{
	int data;
	struct list *next;
};

int is_empty(struct list *head)
{
	return (head == NULL ? 1 : 0);
}

int pop(struct list **head)
{
	struct list *tmp;

	if (!head)
		return -1;

	if (is_empty(*head))
		return -1;

	tmp = *head;
	*head = tmp->next;
	free(tmp);

	return 0;
}

int push(struct list **head, int data)
{
	struct list *elem;

	if (!head)
		return -1;
	
	elem = (struct list*)malloc(sizeof(struct list));
	if (!elem)
		return -1;

	elem->data = data;
	elem->next = *head;

	*head = elem;

	return 0;
}

int peek(struct list *head)
{
	if (!is_empty(head))
		return head->data;
	
	return INVALID_DATA;
}

void stack_print(struct list *head)
{
	if (is_empty(head))
		printf("Stack is empty");

	while (head) {
		printf("%d ", head->data);
		head = head->next;
	}

	printf("\n");
}

int stack_free(struct list **head)
{
	if (!head)
		return -1;

	while(!is_empty(*head))
		pop(head);
}

int main()
{
	struct list *head = NULL;
	int data;

	printf("Enter items:\n");
	do {
		scanf("%d", &data);
		if (data != -1)
			push(&head, data);
	} while (data != -1);

	printf("Stack is:\n");
	stack_print(head);

	printf("How elements to pop?\n");
	scanf("%d", &data);
	while (data) {
		pop(&head);
		data--;
	}

	printf("Stack is:\n");
	stack_print(head);

	printf("Head of stack is:\n");
	data = peek(head);
	if (data != INVALID_DATA)
		printf("%d\n", data);
	else
		printf("Stack is empty\n");

	stack_free(&head);

	return 0;
}
