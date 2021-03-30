#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void swap(char *a, char *b)
{
	char tmp = *a;
	*a = *b;
	*b = tmp;
}

void reverse(char *str)
{
	int len = strlen(str);
	int i;

	for (i = 0; i < len/2; i++)
		swap(str+i, str+len-1-i);
}

int main()
{
	char str[1000];

	printf("Enter a string\n");
	fgets(str, 1000, stdin);
	str[strlen(str)-1] = '\0';

	printf("Original string: %s\n", str);
	reverse(str);
	printf("Reversed string: %s\n", str);

	reverse(str);
	printf("First char is %c (%c)\n", str[0], (str+1)[-1]);

	return 0;
}
