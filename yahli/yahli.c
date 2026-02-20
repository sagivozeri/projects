#include <stdio.h>

int main()
{
	int num;
	char name[100];

	printf("Enter a name:\n");
	scanf("%s", name);
	printf("How many times?\n");
	scanf("%d", &num);
	for (int i = 1; i <= num; i++) {
		printf("%d: %s is very cute\n", i, name);
	}
	return 0;
}
