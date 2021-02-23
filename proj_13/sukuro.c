#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DEBUG printf("[%s][%d]\n", __func__, __LINE__);
#define TABLE_MIN_SIZE 5
#define TABLE_MAX_SIZE 30
#define TABLE_DEFAULT_SIZE 10

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

void fill_row(int **table, int size, int *row_md, int row_id)
{
	int i, j = 0, count = 0;

	for (i = 0; i < size; i++) {
		if (table[row_id][i] == 0) {
			if (count != 0) {
				row_md[j] = count;
				count = 0;
				j++;
			} else {
				continue;
			}
		} else {
			count++;
		}
	}

	if (count)
		row_md[j] = count;
}

void fill_col(int **table, int size, int *col_md, int col_id)
{
	int i, j = 0, count = 0;

	for (i = 0; i < size; i++) {
		if (table[i][col_id] == 0) {
			if (count != 0) {
				col_md[j] = count;
				count = 0;
				j++;
			} else {
				continue;
			}
		} else {
			count++;
		}
	}

	if (count)
		col_md[j] = count;
}

void fill_table_and_md(int **table, int size, int **row_md, int **col_md)
{
	int i,j;

	srand(time(NULL));

	// Fill table
	for (i = 0; i < size; i++)
		for (j = 0; j < size; j++)
			table[i][j] = rand() % 2;

	// Fill row metadata
	for (i = 0; i < size; i++)
		fill_row(table, size, row_md[i], i);

	// Fill col metadata
	for (i = 0; i < size; i++)
		fill_col(table, size, col_md[i], i);
}

void set_size(int *size)
{
	int _size;

	printf("Choose table size between %d-%d\n",
			TABLE_MIN_SIZE, TABLE_MAX_SIZE);
	scanf("%d", &_size);
	if(_size < TABLE_MIN_SIZE || _size > TABLE_MAX_SIZE) {
		printf("Invalid size - set the default size\n");
		_size = TABLE_DEFAULT_SIZE;
	}

	printf("Set table size to %d\n\n", _size);
	*size = _size;
}

void free_table(int **table, int size)
{
	free(table);
}

void find_max(int **row_md, int **col_md, int size, int *max_row, int *max_col)
{
	int i, j, count, max = 0;

	/* row */
	for (i = 0; i < size; i++) {
		count = 0;

		for (j = 0; j < size; j++) {
			if (row_md[i][j])
				count++;
			else
				break;
		}
		
		if (count > max)
			max = count;
	}

	*max_row = max;

	max = 0;

	/* column */
	for (i = 0; i < size; i++) {
		count = 0;
		
		for (j = 0; j < size; j++) {
			if (col_md[i][j])
				count++;
			else
				break;
		}
		
		if (count > max)
			max = count;
	}

	*max_col = max;
}

void print_separate_row(int max_row, int size, char c_start, char c_end)
{
	int i;

	for (i = 0; i < 3*max_row; i++)
		printf("%c", c_start);

	printf("%c", c_start);

	for (i = 0; i < 6*size; i++)
		printf("%c", c_end);

	printf("%c\n", c_end);

}

void print_full_table(int **table, int size, int **row_md, int **col_md,
		      int max_row, int max_col, int show_solution)
{
	int i, j, k;

	print_separate_row(max_row, size, ' ', '-');
	
	for (i = 0; i < max_col; i++) {
		for (k = 0; k < max_row; k++)
			printf("   ");
		printf(" |");
		
		for (j = 0; j < size; j++) {
			if (col_md[j][i])
				printf("  %-2d |", col_md[j][i]);
			else
				printf("     |");
		}

		printf("\n");
	}

	print_separate_row(max_row, size, '-', '=');

	for (i = 0; i < size; i++) {
		printf("|");

		for (j = 0; j < max_row + size; j++) {
			if (j < max_row) {
				if (row_md[i][j])
					printf(" %-2d", row_md[i][j]);
				else
					printf("   ");
			} else {
				if (table[i][j-max_row] && show_solution)
					printf("|  *  ");
				else
					printf("|     ");
			}
		}
		printf("|\n");

		print_separate_row(max_row, size, '-', '=');
	}
}

int main()
{
	int **table, **row_md, **col_md;
	int size, max_row, max_col;

	set_size(&size);
	alloc_table(&table, size);
	alloc_table(&row_md, size);
	alloc_table(&col_md, size);
	fill_table_and_md(table, size, row_md, col_md);
	find_max(row_md, col_md, size, &max_row, &max_col);

	printf("Table before solution\n");
	printf("---------------------\n\n");
	print_full_table(table, size, row_md, col_md, max_row, max_col, 0);

	printf("\n\nFor the solution press Enter\n\n");
	getchar(); getchar();

	printf("Table after solution\n");
	printf("---------------------\n\n");
	print_full_table(table, size, row_md, col_md, max_row, max_col, 1);

	free_table(table, size);

	return 0;
}
