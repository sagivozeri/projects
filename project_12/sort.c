#include <stdio.h>

#define SIZE	100

void swap(int *a, int *b)
{
	int tmp = *a;

	*a = *b;
	*b = tmp;
}

void sort_arr(int *arr, int size)
{
	int *s, *m, *e;

	if (size < 2)
		return;

	s = &arr[0];
	e = &arr[SIZE-1];

	while ((*s) == 1)
		s++;

	while ((*e) == 3)
		e--;

	m = s;

	while (m < e) {
		switch(*m) {
		case 1:
			swap(m, s);
			while ((*s) == 1)
				s++;
			break;
		case 2:
			m++;
			break;
		case 3:
			swap(m, e);
			while ((*e) == 3)
				e--;
			break;
		}
    }
}

void init_arr(int *arr, int size)
{
    int i;

    for (i = 0; i < size; i++)
	arr[i] = (i % 3) + 1;
}

void print_arr(int *arr, int size)
{
    int i;

    for (i = 0; i < size; i++)
	printf("%d ", arr[i]);

    printf("\n");
}

int main()
{
    int arr[SIZE];

    init_arr(arr, SIZE);
    print_arr(arr, SIZE);
    sort_arr(arr, SIZE);
    print_arr(arr, SIZE);

    return 0;
}
