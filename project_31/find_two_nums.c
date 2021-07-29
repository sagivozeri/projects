#include <stdio.h>
#include <stdlib.h>

#define ARR_SIZE 10

unsigned int find_mask(int *a, int n)
{
	unsigned int mask = 1;
	int combined = 0, i;

	for (i = 0 ; i < n ; i++)
		combined = combined ^ a[i];

	printf("combined = 0x%x\n", combined);

	while ((combined & mask) == 0)
		mask = mask * 2;

	return mask;
}

void get_unique_numbers(int *a, int n, int *j, int *k)
{
	int i, j1 = 0, k1 = 0;
	unsigned int mask;

	mask = find_mask(a, n);

	printf("mask = 0x%x\n", mask);

	for (i = 0 ; i < n ; i++) {
		if ((a[i] & mask) == 0)
			j1 = j1 ^ a[i];
		else
			k1 = k1 ^ a[i];
	}

	*j = j1;
	*k = k1;
}

int main()
{
	int a[ARR_SIZE] = {10, 20, 30, 20, 10, 40, 40, 50, 50, 60};
	int j, k;

	get_unique_numbers(a, ARR_SIZE, &j, &k);

	printf("Unique numbers are: %d, %d\n", j, k);

	return 0;
}
