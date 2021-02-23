#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *bits = NULL;
int size = 0;

void print_bitarray()
{
	int i;

	for (i = 0; i < size; i++)
		printf("%d ", bits[i]);

	printf("\n");
}

int sub_seq(int *A, int _size, int sum)
{
	if (!sum)
		return 1;

	if (_size == 0)
		return 0;

	bits[_size-1] = 1;
	if (sub_seq(A, _size-1, sum-A[_size-1]))
		print_bitarray();
	bits[_size-1] = 0;
	if (sub_seq(A, _size-1, sum))
		print_bitarray();

	return 0;
}

int main()
{
	int *array = NULL;
	int sum, i;

	printf("Enter array size\n");
	scanf("%d", &size);

	array = (int*)malloc(sizeof(int) * size);
	if (!array)
		return 1;

	bits = (int*)malloc(sizeof(int) * size);
	if (!bits)
		return 1;

	printf("Enter %d numbers\n", size);
	for (i = 0; i < size; i++)
		scanf("%d", &array[i]);

	printf("Enter sum\n");
	scanf("%d", &sum);

	printf("\n");
	printf("Array: ");
	for (i = 0; i < size; i++)
		printf("%d ", array[i]);
	printf("; sum = %d\n", sum);
	printf("\n");
	printf("Bitmaps:\n");

	sub_seq(array, size, sum);

	free(array);
	free(bits);

	return 0;
}
