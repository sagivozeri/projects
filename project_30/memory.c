#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct student {
	int age;
	int grade;
	int hight;
	int weight;
};

int main(int argc, char **argv)
{
	int *addr1 = NULL, *addr2 = NULL;
	int val1 = 30, val2 = 0;
	struct student s1, s2;

	addr2 = &val2;

	printf("addr1 = %p, addr2 = %p, val1 = %d, val2 = %d, "
		"*addr1 = %d, *addr2 = %d\n", addr1, addr2, val1, val2, *addr1,
		*addr2);

	memcpy(&val2, &val1, sizeof(int));

	printf("addr1 = %p, addr2 = %p, val1 = %d, val2 = %d, "
		"*addr1 = %d, *addr2 = %d\n", addr1, addr2, val1, val2, *addr1,
		*addr2);

	return 0;
}
