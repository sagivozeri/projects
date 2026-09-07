#include <stdio.h>
#include <stdlib.h>

void print_common_values(int a1[], int a2[], int n, int m) {
  int i = 0, j = 0;

  printf("Common values: ");

  while (i < n && j < m) {
    if (a1[i] < a2[j])
      i++;
    else if (a1[i] > a2[j])
      j++;
    else {
      int val = a1[i];
      i++;
      j++;

      printf("%d ", val);

      while (i < n && a1[i] == val)
        i++;
      while (j < m && a2[j] == val)
        j++;
    }
  }

  printf("\n");
}

// 1 1 1 2 2 2 3 4
// 1 1 2 2 3 3 4 5
#define SIZE1 10
#define SIZE2 20

#define MODULE 10

void print_arr(const char *str, int a[], int n) {
  int i;

  printf("%s: ", str);

  for (i = 0; i < n; i++)
    printf("%d ", a[i]);

  printf("\n");
}

// Custom comparator
int comp(const void *a, const void *b) {
  // If a is smaller, positive value will be returned
  return (*(int *)a - *(int *)b);
}

int main() {
  int a1[SIZE1], a2[SIZE2];
  int i;

  for (i = 0; i < SIZE1; i++)
    a1[i] = rand() % MODULE;

  for (i = 0; i < SIZE2; i++)
    a2[i] = rand() % MODULE;

  print_arr("a1", a1, SIZE1);
  print_arr("a2", a2, SIZE2);

  qsort(a1, SIZE1, sizeof(int), comp);
  qsort(a2, SIZE2, sizeof(int), comp);

  print_arr("sorted a1", a1, SIZE1);
  print_arr("sorted a2", a2, SIZE2);

  print_common_values(a1, a2, SIZE1, SIZE2);
}
