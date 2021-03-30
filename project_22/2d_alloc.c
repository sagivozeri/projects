#include <stdio.h>
#include <stdlib.h>

#define ROWS 3
#define COLS 5

int **A;

void my_2d_alloc()
{
	int i;
	
	A = (int **)malloc(ROWS * sizeof(int*));

	for (i = 0; i < ROWS; i++)
		A[i] = (int *)malloc(sizeof(int) * COLS);
}

void my_2d_free()
{
	int i;

	for (i = 0; i < ROWS; i++)
		free(A[i]);

	free(A);
}

void my_2d_print()
{
	int i, j;

	for (i = 0; i < ROWS; i++) {
		for (j = 0; j < COLS; j++)
			printf("%d\t", A[i][j]);
		printf("\n");
	}
}

void my_2d_fill()
{
	int i, j, val = 0;
	
	for (i = 0; i < ROWS; i++)
		for (j = 0; j < COLS; j++) {
			A[i][j] = val;
			val++;
		}
}

int main()
{
	my_2d_alloc();
	my_2d_fill();
	my_2d_print();
	my_2d_free();

	return 0;
}
