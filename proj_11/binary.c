#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef unsigned char u8;
typedef unsigned long u32;
typedef unsigned long long u64;

#define MASK 0x1

struct example
{
	u8 a;
	u8 b;
	bool c;
};

#define CNT 1

int main(void)
{
	struct example ex;
	bool c1;
	int cnt = CNT;

	memset(&ex, 0xff, sizeof(ex));
	c1 = ex.c;

	printf("c1 = 0x%x, MASK = 0x%x, c1 & MASK = 0x%x\n", c1, MASK, (u8)(c1 & MASK));

	while (--cnt) {
		printf("%d\n", cnt);
	}

	return 0;
}
