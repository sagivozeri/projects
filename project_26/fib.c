#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long u64;

u64 *fib;

u64 calc_fib1(int n)
{
	if (n == 1 || n == 2)
		return n-1;

	if (fib[n])
		return fib[n];

	fib[n] = calc_fib1(n-1) + calc_fib1(n-2);
	return fib[n];
}

u64 calc_fib2(int n)
{
	if (n == 1 || n == 2)
		return n-1;

	return calc_fib2(n-1) + calc_fib2(n-2);
}

int main()
{
	int n;
	u64 val;

	printf("Enter a number:\n");
	scanf("%d", &n);

	fib = (u64 *)calloc(n+1, sizeof(u64));
	if (!fib)
		return -1;

	printf("Before short calc_fib1\n");
	val = calc_fib1(n);
	printf("After short calc_fib1 n = %d val = %llu\n", n, val);

	printf("Before long calc_fib2\n");
	val = calc_fib2(n);
	printf("After long calc_fib2 n = %d val = %llu\n", n, val);

	free(fib);

	return 0;
}
