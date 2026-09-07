#include <stdio.h>
#include <stdlib.h>

typedef struct list {
  int data;
  struct list *next;
} List;

int list_add_back(List **head, int d) {
  List **tmp, *new;

  tmp = head;

  while (*tmp)
    tmp = &((*tmp)->next);

  new = malloc(sizeof(List *));
  if (!new)
    return -1;

  new->data = d;
  new->next = NULL;

  *tmp = new;

  return 0;
}

void list_del_back(List **head) {
  List **tmp = head;

  if (!(*tmp))
    return;

  while ((*tmp)->next)
    tmp = &((*tmp)->next);

  free(*tmp);
  *tmp = NULL;
}

void list_reverse(List **head) {
  List *prev = NULL, *curr, *next;

  curr = *head;

  if (!curr)
    return;

  while (curr->next) {
    next = curr->next;
    curr->next = prev;
    prev = curr;
    curr = next;
  }

  curr->next = prev;
  *head = curr;
}

void list_print(List *head) {
  printf("List: ");
  while (head) {
    printf("%d ", head->data);
    head = head->next;
  }
  printf("\n");
}

void list_free(List **head) {
  List *curr = *head, *tmp;

  while (curr) {
    tmp = curr;
    curr = curr->next;
    free(tmp);
  }

  *head = NULL;
}

int list_del_nth_and_return_val(List **head, int n, int *data) {
  List **curr = head, *tmp;
  int pos = n;

  if (n < 1) {
    printf("Invalid position %d\n", pos);
    return -1;
  }

  if (!data) {
    printf("Invalid data pointer\n");
    return -1;
  }

  if (!head || !(*head)) {
    printf("List is empty\n");
    return -1;
  }

  while (n > 1) {
    curr = &(*curr)->next;
    n--;

    if (!(*curr)) {
      printf("No entry in pos %d\n", pos);
      return -1;
    }
  }

  tmp = *curr;
  *curr = (*curr)->next;

  *data = tmp->data;
  free(tmp);

  printf("Removed element from pos %d with data %d\n", pos, *data);

  return 0;
}

int main() {
  List *head = NULL;
  int val;

  list_add_back(&head, 1);
  list_add_back(&head, 6);
  list_add_back(&head, 2);
  list_add_back(&head, 5);
  list_add_back(&head, 3);
  list_add_back(&head, 4);
  list_add_back(&head, 8);
  list_add_back(&head, 7);
  list_print(head);

  list_reverse(&head);
  list_print(head);

  list_del_back(&head);
  list_print(head);

  list_del_nth_and_return_val(&head, 3, &val);
  list_print(head);

  list_del_nth_and_return_val(&head, 0, &val);
  list_print(head);

  list_del_nth_and_return_val(&head, 4, &val);
  list_print(head);

  list_del_back(&head);
  list_print(head);

  list_del_nth_and_return_val(&head, 5, &val);
  list_print(head);

  list_del_nth_and_return_val(&head, 1, &val);
  list_print(head);

  list_del_nth_and_return_val(&head, 1, &val);
  list_print(head);

  list_del_nth_and_return_val(&head, 1, &val);
  list_print(head);

  list_del_nth_and_return_val(&head, 1, &val);
  list_print(head);

  list_del_nth_and_return_val(&head, 1, &val);
  list_print(head);

  list_free(&head);
  list_print(head);

  return 0;
}
