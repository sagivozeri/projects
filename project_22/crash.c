#include <stdio.h>

int main()
{
	int arr[10];
	int i;

	for (i = 0; i < 200000; i++)
		printf("%d\n", arr[i]);

	return 0;
}
