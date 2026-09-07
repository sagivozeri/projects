#include <stdio.h>
#include <stdlib.h>

typedef struct _list {
  int val;
  struct _list *next;
} list;

static int delete_nth_elem(list **head, int n, int *val) {
  list *tmp, **curr = head;

  if (!head || !(*head) || n <= 0 || !val) {
    printf("Invalid input\n");
    return -1;
  }

  printf("curr = %p\n", curr);

  for (int i = 1; i < n; i++) {
    curr = &((*curr)->next);
    printf("curr = %p\n", curr);
    if (!(*curr)) {
      printf("No %d elements in the list\n", n);
      return -1;
    }
  }

  tmp = *curr;
  *curr = (*curr)->next;
  *val = tmp->val;

  return 0;
}

void print_list(list *head) {
  printf("List: ");
  while (head) {
    printf("%d ", head->val);
    head = head->next;
  }
  printf("\n");
}

int main() {
  list x, y, z, *head;
  int rc, val;

  head = &x;
  x.val = 1;
  x.next = &y;
  y.val = 2;
  y.next = &z;
  z.val = 3;
  z.next = NULL;

  printf("head %p x.next %p y.next %p z.next %p\n", head, x.next, y.next,
         z.next);
  printf("&head %p &x.next %p &y.next %p &z.next %p\n", &head, &(x.next),
         &(y.next), &(z.next));

  print_list(head);

  rc = delete_nth_elem(&head, 3, &val);
  if (rc)
    return 1;

  printf("val = %d\n", val);

  print_list(head);

  return 0;
}
