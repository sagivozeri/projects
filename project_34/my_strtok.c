#include <stdio.h>

char * my_strtok(char *str, const char del)
{
	char *s;
	static char *start = NULL;
	int i = 0;

	if (str == NULL)
		s = start;
	else
		s = str;

	if (s == NULL || s[0] == '\0')
		return NULL;

	while(s[i] != del && s[i] != '\0')
		i++;

	s[i] = '\0';
	i++;

	while(s[i] == del)
		i++;

	start = &s[i];

	return s;
}

int main()
{
	char str[100] = "My name is Sagiv";
	char *s;
	
	s = my_strtok(str, '-');
	while (s != NULL) {
		printf("%s\n", s);
		s = my_strtok(NULL, '-');
	}

	return 0;
}