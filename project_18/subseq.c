#include <stdio.h>
#include <stdlib.h>

int sub_seq(int *arr, int *res, int size, int num)
{
	int rc;

	if (num == 0)
		return 0;

	if (size == 0)
		return 1;

	res[size-1] = 1;
	if (!sub_seq(arr, res, size-1, num-arr[size-1]))
		return 0;

	res[size-1] = 0;
	return sub_seq(arr, res, size-1, num);
}

int main()
{
	int *arr, *res;
	int size, num, rc, i;
	time_t t;

	srand((unsigned)time(&t));

	printf("Enter size: ");
	scanf("%d", &size);

	arr = (int*)malloc(sizeof(int) * size);
	res = (int*)malloc(sizeof(int) * size);

	for (i = 0; i < size; i++) {
		arr[i] = rand() % 100;
		res[i] = 0;
	}

	printf("Array is:\n");
	for (i = 0; i < size; i++)
		printf("%d ", arr[i]);

	printf("\n");

	printf("Enter num: ");
	scanf("%d", &num);

	rc = sub_seq(arr, res, size, num);
	if (!rc) {
		printf("Found!\n");
		for (i = 0; i < size; i++)
			printf("%d ", res[i]);
		printf("\n");
	} else {
		printf("Not found!\n");
	}

	free(arr);
	free(res);

	return 0;
}
