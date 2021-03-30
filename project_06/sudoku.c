#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROW_OFFSET 0
#define COL_OFFSET 9
#define SQR_OFFSET 18

int Table[9][9];
int Checked[27][9];
int Used[81];
int debug = 0;
int def = 0;

void print_table(int opt)
{
	int i, j;

	switch(opt) {
	case 1:
		for (i = 0; i < 9; i++) {
			if (i%3 == 0)
				printf("||=====================================||\n");
			else
				printf("||-------------------------------------||\n");
			printf("||");

			for (j = 0; j < 9; j++)
				if ((j+1)%3 == 0)
					printf(" %d ||", Table[i][j]);
				else
					printf(" %d |", Table[i][j]);

			printf("\n");
		}
		printf("||=====================================||\n");
		break;
	case 2:
		if (!debug)
			return;

		for (i = 0; i < 27; i++) {
			if (i == ROW_OFFSET)
				printf("Rows:\n");
			if (i == COL_OFFSET)
				printf("Columns:\n");
			if (i == SQR_OFFSET)
				printf("Squares:\n");

			printf("|-----------------------------------|\n");
			printf("|");
			
			for (j = 0; j < 9; j++)
				printf(" %d |", Checked[i][j]);

			printf("\n");
		}
		printf("|-----------------------------------|\n");
		break;
	case 3:
		if (!debug)
			return;

		for (i = 0; i < 9; i++) {
			printf("|-----------------------------------|\n");
			printf("|");
			
			for (j = 0; j < 9; j++)
				printf(" %d |", Used[i*9 + j]);

			printf("\n");
		}
		printf("|-----------------------------------|\n");
		break;
	}

	printf("\n");
}

int get_sqr_idx(int i, int j)
{
	int row = i/3, col = j/3;

	if (row == 0 && col == 0) return 0;
	if (row == 0 && col == 1) return 1;
	if (row == 0 && col == 2) return 2;
	if (row == 1 && col == 0) return 3;
	if (row == 1 && col == 1) return 4;
	if (row == 1 && col == 2) return 5;
	if (row == 2 && col == 0) return 6;
	if (row == 2 && col == 1) return 7;
	if (row == 2 && col == 2) return 8;
}

int check_table()
{
	int i, j, val, is_invalid = 0;

	memset(Checked, 0, sizeof(int)*9*27);

	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			val = Table[i][j];

			if (val == 0)
				continue;

			if (Checked[ROW_OFFSET+i][val-1])
				is_invalid = 1;
			if (Checked[COL_OFFSET+j][val-1])
				is_invalid = 1;
			if (Checked[SQR_OFFSET + get_sqr_idx(i,j)][val-1])
				is_invalid = 1;

			if (is_invalid) {
				return 1;
			}

			Checked[ROW_OFFSET+i][val-1] = 1;
			Checked[COL_OFFSET+j][val-1] = 1;
			Checked[SQR_OFFSET + get_sqr_idx(i,j)][val-1] = 1;

			print_table(2);
		}
	}

	return 0;
}

void mark_used_indices()
{
	int idx, row, col;

	for (idx = 0; idx < 81; idx++) {
		row = idx / 9;
		col = idx % 9;

		if (Table[row][col])
			Used[idx] = 1;
	}
}

int solve_table(int idx, int val)
{
	int row, col;

	if (idx == 81)
		return 0;

	row = idx / 9;
	col = idx % 9;

	if (val == 10) {
		Table[row][col] = 0;
		return 1;
	}

	if (Used[idx])
		return solve_table(idx+1, 1);

	Table[row][col] = val;

	if (check_table() || solve_table(idx+1, 1))
		return solve_table(idx, val+1);
}

void add_table()
{
	int row = 0, col;
	char val[10];

	if (def)
		return;

	printf("Add sudoku table:\n");
	while (row < 9) {
		printf("Enter row %d\n", row+1);
		scanf("%s", val);

		for (col = 0; col < 9; col++)
			Table[row][col] = val[col]-'0';
		
		row++;
	}
	printf("\n");
}

int main(int argc, char *argv[])
{
	if (argc == 2) {
		if (!strcmp(argv[1], "debug"))
			debug = 1;
		if (!strcmp(argv[1], "default"))
			def = 1;
		if (!strcmp(argv[1], "all"))
			debug = def = 1;
	}

	add_table();

	printf("Table to solve:\n");
	print_table(1);

	mark_used_indices();
	print_table(3);

	solve_table(0, 1);

	printf("Solution:\n");
	print_table(1);

	return 0;
}
