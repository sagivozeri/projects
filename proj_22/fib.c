#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int fib(int n)
{
	if (n == 0 || n == 1)
		return n;

	return fib(n-1) + fib(n-2);
}

int fib_fast(int n, int *mem)
{
	if (n == 0 || n == 1)
		return n;

	if (!mem[n])
		mem[n] = fib_fast(n-1, mem) + fib_fast(n-2, mem);

	return mem[n];
}

int main()
{
	int *mem;
	int n, res;

	printf("Enter n:\n");
	scanf("%d", &n);

	if (n < 0) {
		printf("Invalid input\n");
		return 1;
	}

	mem = (int*)malloc(sizeof(int) * (n+1));
	if (!mem) {
		printf("Allocation failed\n");
		return 1;
	}

	memset(mem, 0, (n+1) * sizeof(int));

	res = fib(n);
	printf("REGULAR: The fib value of element %d is %d\n", n, res);

	res = fib_fast(n, mem);
	printf("FAST: The fib value of element %d is %d\n", n, res);

	free(mem);

	return 0;
}
