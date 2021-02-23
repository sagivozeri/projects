#include <stdio.h>
#include <string.h>

#define MAX_STR_SIZE 1000

void urlify(char *str, int real_size)
{
	int new_size, spaces = 0;
	int i;

	/* Count the number of spaces */
	for (i = 0; i < real_size; i++)
		if (str[i] == ' ')
			spaces++;

	new_size = real_size + spaces*2;

	str[new_size] = '\0';
	new_size--;

	for (i = real_size-1; i > 0; i--) {
		if (str[i] == ' ') {
			str[new_size] = '0';
			str[new_size-1] = '2';
			str[new_size-2] = '%';
			new_size -= 3;
		} else {
			str[new_size] = str[i];
			new_size--;
		}
	}
}

int main()
{
	char str[MAX_STR_SIZE];

	printf("Enter string:\n");
	fgets(str, MAX_STR_SIZE, stdin);

	if (strlen(str) > 0 && str[strlen(str)-1] == '\n')
		str[strlen(str)-1] = '\0';

	printf("Old str %s size %d\n", str, strlen(str));
	urlify(str, strlen(str));
	printf("New str %s size %d\n", str, strlen(str));

	return 0;
}
