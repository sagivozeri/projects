#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 0
int is_unique(const char *str)
{
	int len = strlen(str);
	int bucket[256] = {0};
	int i, ascii_val;

	for (i = 0; i < len; i++) {
		ascii_val = str[i];
		if (bucket[ascii_val] > 0)
			return 0;
		bucket[ascii_val]++;
	}
	
	return 1;
}
#else
int is_unique(const char *str)
{
	int len = strlen(str);
	int i, j;

	for (i = 0; i < len; i++)
		for (j = i+1; j < len; j++)
			if (str[i] == str[j])
				return 0;

	return 1;
}
#endif

int main()
{
	char str[1000];

	printf("Enter a string:\n");
	scanf("%s", str);

	printf("The string %s uniqe\n", is_unique(str) ? "is" : "isn't");

	return 0;
}
