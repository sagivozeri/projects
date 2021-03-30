#include <stdio.h>
#include <stdlib.h>

int swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void sort(int A[], int n)
{
	int s=0, c=0, e=n-1;

	if (n < 2)
		return;

	/* Set c to be the index of the first non 0 */
	while (A[c] == 0)
		c++;

	/* Sort the array */
	while (c < e) {
		switch (A[c]) {
			case 1: c++;
					break;
			case 0: swap(&A[c], &A[s]);
					s++;
					break;
			case 2: swap(&A[c], &A[e]);
					e--;
					break;
		}
	}
}

void print_arr(int A[], int n)
{
	int i;

	for (i = 0; i < n; i++)
		printf("%d ", A[i]);

	printf("\n");
}

int main()
{
	int *A, n, i, val;

	printf("Enter array size\n");
	scanf("%d", &n);

	A = (int*)malloc(sizeof(int) * n);
	if (!A) {
		printf("Allocation failed\n");
		return 1;
	}

	printf("Enter %d numbers between 0-2\n", n);
	for (i = 0; i < n; i++) {
		scanf("%d", &val);
		if (val >= 0 && val <= 2) {
			A[i] = val;
		} else {
			printf("wrong value! please insert again\n");
			i--;
		}
	}

	printf("The array before sorting is:\n");
	print_arr(A, n);
	sort(A, n);
	printf("The array after sorting is:\n");
	print_arr(A, n);
	
	free(A);

	return 0;
}
