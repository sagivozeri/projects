#include <stdio.h>
#include <string.h>

#define MAX_NUM_STR 1000

int is_letter(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (c - 'A');
	
	if (c >= 'a' && c <= 'z')
		return (c - 'a');

	return -1;
}

int is_palindrom(const char *str)
{ 
	int i, bitmap = 0, val;
	int len = strlen(str);

	for (i = 0; i < len; i++) {
		val = is_letter(str[i]);
		if (val >= 0)
			bitmap ^= 1 << val;
	}

	if (((bitmap-1) & bitmap) == 0)
		return 1;

	return 0;
}

int main()
{
	char str[MAX_NUM_STR];

	printf("Enter a string:\n");
	fgets(str, MAX_NUM_STR, stdin);

	if (strlen(str) > 0 && str[strlen(str)-1] == '\n')
		str[strlen(str)-1] = '\0';

	printf("String %s %s a palindrom permutation\n",
			str, is_palindrom(str) ? "is" : "isn't");

	return 0;
}
