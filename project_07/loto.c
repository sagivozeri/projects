#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned long long u64;

int g_total_size = 0;
int g_perm_size = 0;
int g_debug = 0;


int num_to_bits[256] =
{0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4,
 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8};

#if 1
/* Recursively get byte of a given number and map them in the array  */
unsigned int get_bit_number(u64 num)
{
	int byte = 0;

	if (0 == num)
		return num_to_bits[0];

	// Find last byte
	byte = num & 0xff;

   	// Use pre-stored values to find count
   	// in last byte plus recursively add
   	// remaining bytes.
	return num_to_bits[byte] + get_bit_number(num >> 8);
}
#else
unsigned int get_bit_number(u64 num)
{
	unsigned char bytes[8] = {0};
	unsigned int bit_num = 0;
	int i;

	for (i = 0; i < 8; i++)
		bytes[i] = (num >> i*8) & 0xff;

	for (i = 0; i < 8; i++)
		bit_num += num_to_bits[bytes[i]];

	return bit_num;
}
#endif

void print_bits(u64 num)
{
	int i;

	if (!g_debug)
		return;

	for (i = 0; i < 64; i++) {
		if ((num >> i) & 0x1)
			printf("%d ", i + 1);
	}

	printf("\n");
}

u64 calc_perm()
{
	u64 max_iter = 1;
	u64 mask, count = 0;
	int i;

	for (i = 0; i < g_total_size; i++)
		max_iter *= 2;

	for (mask = 0; mask < max_iter; mask++) {
		if (get_bit_number(mask) == g_perm_size) {
			print_bits(mask);
			count++;
		}
	}

	return count;
}

u64 test()
{
	u64 max_iter = 1;
	u64 count = 0;
	u64 i, j, k;

	for (i = 0; i < g_total_size; i++)
		max_iter *=2;

	printf("max_iter = %llu\n", max_iter);

	for (i = 0; i < max_iter; i++) {
		for (j = 0; j < 64; j++)
			k = 1;
		count++;
	}

	return count;
}

int main(int argc, char *argv[])
{
	u64 num_perm = 0;

	if (argc < 3) {
		printf("no enough arguments\n");
		return 1;
	} else if (argc > 4) {
		printf("too many arguments\n");
		return 1;
	} else if (argc == 4) {
		g_debug = 1;
	}

	g_total_size = atoi(argv[1]);
	g_perm_size = atoi(argv[2]);

	num_perm = calc_perm();
	//num_perm = test();

	printf("num_perm = %llu\n", num_perm);

	return 0;
}
