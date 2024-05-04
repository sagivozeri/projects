#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	int i;

	printf("number of inputs %d\n", argc);
	for (i = 0; i < argc ; i++)
		printf("input %d: %s\n", i, argv[i]);

	return 0;
}