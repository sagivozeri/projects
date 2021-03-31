#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	int a[10] = {1, 5, 7, 2, 4, 6, 9, 3, 8, 0};
	int max_val = a[0], max_idx = 0;
	int sum = 0;
	int i;

	for (i = 0; i < 10; i++) {
		if (a[i] > max_val) {
			max_val = a[i];
			max_idx = i;
		}

		sum = sum + a[i];
	}

	printf("max_val = %d, max_idx = %d, avg = %lf\n", max_val, max_idx, (double)sum/10);

	return 0;
}
