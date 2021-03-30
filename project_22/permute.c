#include <stdio.h>
#include <string.h>

void swap(char *a, char *b)
{
	char tmp = *a;
	*a = *b;
	*b = tmp;
}

void permute(char *str, int s, int e)
{
	int i;

	if (s == e) {
		printf("%s\n", str);
		return;
	}

	for (i = s; i <= e; i++) {
		swap(str+s, str+i);
		permute(str, s+1, e);
		swap(str+s, str+i);
	}
}

int main()
{
	char str[] = "ABCD";

	permute(str, 0, strlen(str)-1);

	return 0;
}
