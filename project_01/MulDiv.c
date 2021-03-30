#include <stdio.h>
#include <stdlib.h>

int MulFunc(int a, int b)
{
	int i, res = 0;

	for (i = 0; i < 32; i++)
		res += (b & (1 << i)) ? a << i : 0;

	return res;
}

int DivFunc(int a, int b)
{
	int i, res = 0;
	unsigned long long a1 = a, b1 = b;

	for (i = 31; i >= 0; i--) {
		if (a1 >= (b1 << i)) {
			a1 -= b1 << i;
			res |= 1 << i;
		}
	}

	return res;
}

int main(int argc, char *argv[])
{
	int val1, val2, resMul, resDiv;

	if (argc != 3) {
		printf("wrong input - need two params\n");
		return 1;
	}

	val1 = atoi(argv[1]);
	val2 = atoi(argv[2]);

	resMul = MulFunc(val1, val2);
	resDiv = DivFunc(val1, val2);

	printf("Multiplication result is %d\n", resMul);
	printf("Division result is %d\n", resDiv);

	return 0;
}
