#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int num;

	if (argc == 2) {
		num = atoi(argv[1]);
	} else {
		printf("Bad num of args\n");
		return 1;
	}

	printf("%s: number is %s\n",argv[0], (num == 1) ? "one" : ((num == 2) ? "two" : "other"));

	return 0;
}
