#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

int is_pair(int arr[], int size, int sum, int *idx1, int *idx2)
{
	struct entry *ent;
	int i, idx, key, val;

	for (i = 0; i < size; i++) {
		val = sum - arr[i];
		key = hash(val);

		idx = hash_get(key, val);
		if (idx >= 0) {
			*idx1 = idx;
			*idx2 = i;
			return 0;
		}

		ent = (struct entry *)malloc(sizeof(*ent));
		if (!ent) {
			printf("Allocation failed\n");
			return 1;
		}

		key = hash(arr[i]);
		ent->num = arr[i];
		ent->idx = i;
		ent->next = NULL;

		hash_set(key, ent);
	}

	return 1;
}

int main()
{
	int *arr;
	int size, i, sum;
	int rc, i1, i2;
    time_t t;

	printf("Enter array size: ");
	scanf("%d", &size);

	table_size = size * 2;

	if (hash_alloc())
		return 1;
	
	arr = (int*)malloc(sizeof(int) * size);
	if (!arr) {
		printf("Allocation failed\n");
		return 1;
	}

    srand((unsigned)time(&t));

	/* Fill array with random numbers */
	for (i = 0; i < size; i++)
		arr[i] = rand() % 51;

	printf("The array is:\n");
	for (i = 0; i < size; i++)
		printf(" %2d ", i+1);

	printf("\n");

	for (i = 0; i < size; i++)
		printf(" %2d ", arr[i]);

	printf("\n");

	printf("Enter sum: ");
	scanf("%d", &sum);

	rc = is_pair(arr, size, sum, &i1, &i2);
	if (rc)
		printf("There is no pair that equal to %d\n", sum);
	else
		printf("A pair was found in indices %d and %d\n", i1+1, i2+1);

	//hash_display();

	hash_free();
	free(arr);

    return 0;
}

