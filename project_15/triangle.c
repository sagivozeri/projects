#include <stdio.h>
#include <stdlib.h>

int alloc_table(int ***table, int size)
{
	int len = 0, i;
	int *ptr, **_table;

	len = sizeof(int *) * size + sizeof(int) * size * size;
	_table = (int **)malloc(len);

	if (!_table) {
		printf("allocation failed\n");
		return -1;
	}

	// ptr is now pointing to the first element in of 2D array
	ptr = (int *)(_table + size);

	// for loop to point rows pointer to appropriate location in 2D array
	for(i = 0; i < size; i++)
		_table[i] = (ptr + size * i);

	*table = _table;

	return 0;
}

void free_table(int **table, int size)
{
	free(table);
}

void zero_table(int **table, int size)
{
	int i,j;

	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
			table[i][j] = 0;
}

void print_drawing(int **table, int size)
{
	int i,j;

	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			if (table[i][j])
				printf("*");
			else
				printf(" ");
		}
		printf("\n");
	}
}

void draw_triangle(int **table, int h, int upside_down, int off)
{
	int offset, dots, i, j;
	int start = off, end = off+h;

	if (off > h)
		return;

	for (i = start; i < end; i++) {
		offset = upside_down ? i-off : h-1-(i-off);
		dots = upside_down ? 2*h-1-2*(i-off) : 2*(i-off)+1;

		j = 0;

		while (offset) {
			j++;
			offset--;
		}

		while (dots) {
			table[i][j] = 1;
			j++;
			dots--;
		}
	}
}

void draw_triangle_regular(int **table, int size, int h)
{
	zero_table(table, size);
	draw_triangle(table, h, 0, 0);
	print_drawing(table, size);
}

void draw_triangle_upside_down(int **table, int size, int h)
{
	zero_table(table, size);
	draw_triangle(table, h, 1, 0);
	print_drawing(table, size);
}

void draw_diamond(int **table, int size, int h)
{
	zero_table(table, size);
	draw_triangle(table, h, 0, 0);
	draw_triangle(table, h, 1, h-1);
	print_drawing(table, size);
}

void draw_david(int **table, int size, int h)
{
	zero_table(table, size);
	draw_triangle(table, h, 0, 0);
	draw_triangle(table, h, 1, h/2);
	print_drawing(table, size);

}

int main(){
	int **table;
	int h, size;

	printf("choose triangle height\n");
	scanf("%d", &h);
	printf("\n");

	if (h <= 0)
		return -1;

	size = 2*h-1;

	alloc_table(&table, size);
	zero_table(table, size);

	printf("A triangle in height %d\n\n", h);
	draw_triangle_regular(table, size, h);
	printf("\n");

	printf("An upside-down triangle in height %d\n\n", h);
	draw_triangle_upside_down(table, size, h);
	printf("\n");

	printf("A diamond in height %d\n\n", size);
	draw_diamond(table, size, h);
	printf("\n");

	if (h >=5) {
		printf("A \"star of david\" in height %d\n\n", size);
		draw_david(table, size, h);
		printf("\n");
	}

	free_table(table, size);

	return 0;
}
