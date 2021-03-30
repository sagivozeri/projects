#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int i, j;

	for (i = 0; i < 10; i++) {
		printf("start of loop i = %d\n", i);

		for (j = 0; j < 10; j++) {
			printf("start of inner loop j = %d\n", j);
			if (i > 5 && j == 4)
				break;
			printf("end of inner loop j = %d\n", j);
		}

		printf("end of loop i = %d\n", i);
	}

	return 0;
}
