#include <stdio.h>
#include <stdlib.h>

int flip(int x)
{
	return (x ^ 0x1);
}

int sign(int x)
{
	return flip((((unsigned long)x) >> 31) & 0x1);
}

int get_max(int a, int b)
{
	int sa = sign(a);
	int sb = sign(b);
	int sign_diff = sign(a - b);

	int use_sign_a = sa ^ sb;
	int use_sign_diff = flip(use_sign_a);

	int k = use_sign_a * sa + use_sign_diff * sign_diff;
	int q  = flip(k);

	return (a * k + b * q);
}

int main(int argc, char *argv[])
{
	int a, b, max;
	
	if (argc != 3) {
		printf("Num of args should be 2!\n");
		return -1;
	}

	a = strtol(argv[1], NULL, 16);
	b = strtol(argv[2], NULL, 16);
	max = get_max(a, b);
	printf("Max of %d and %d is %d\n", a, b, max);

	return 0;
}
