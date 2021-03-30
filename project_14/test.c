#include <stdio.h>

int main()
{
	unsigned int a, b, c;

	a = 10;
	b = 0xFFFFFFFF;

	c = a - b;

	printf("a=0x%x, b=0x%x, c=0x%x\n", a,b,c);
}
