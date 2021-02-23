#include <stdlib.h>
#include <stdio.h>

#define SIZE	100
#define LOOP	for (int i = 0; i < SIZE; i++)

int main()
{
	int a[SIZE];

	LOOP {
		a[i] = i + 10;
	}

	LOOP {
		a[i] = a[i] - 1;
	}

	LOOP {
		printf("a[%d] = %d\n", i, a[i]);
	}

	return 0;
}
