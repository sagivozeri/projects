#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void f(int *array, int size)
{
	for (int i = 0; i < 64; i++)
		printf("array[%d] = %d\n", i, array[i]);

	printf("sizeof(array) = %d\n", sizeof(array));
}

int main()
{
	int *array = (int*)malloc(sizeof(*array) * 64);

	for (int i = 0; i < 64; i++)
		array[i] = i;

	f(array, 64);
	memset(array, 0xff, sizeof(*array));
	f(array, 64);

	free(array);

	return 0;
}
