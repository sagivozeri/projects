#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void _print_str(const char *str, int len)
{
	int i = 0;
	int found = 0;

	for (i = 0; i < len; i++)
		if (str[i]) {
			printf("%c", str[i]);
			found = 1;
		}

	if (found)
		printf("\n");
}

int find_free_idx(const char *str, int len)
{
	int i = 0;

	for (i = 0; i < len; i++)
		if (!str[i]) return i;

	printf("WARN - No free idx\n");
	return 0;
}

void print_subsets(char *str, int len, char *print_str, int orig_len)
{
	int idx;
	char c;

	if (len == 0) {
		_print_str(print_str, orig_len);
		return;
	}

	print_subsets(str+1, len-1, print_str, orig_len);
	idx = find_free_idx(print_str, orig_len);
	print_str[idx] = str[0];
	print_subsets(str+1, len-1, print_str, orig_len);
	print_str[idx] = '\0';
}

#define STR_MAX_LEN 100

int main()
{
	char str[STR_MAX_LEN];
	char print_str[STR_MAX_LEN];
	int i, orig_len;

	printf("Enter string:\n");
	fgets(str, STR_MAX_LEN-1, stdin);
	str[strlen(str) - 1] = '\0';

	orig_len = strlen(str);

	for (i = 0; i < STR_MAX_LEN; i++)
		print_str[i] = '\0';

	print_subsets(str, orig_len, print_str, orig_len);

	return 0;
}
