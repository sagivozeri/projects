/* Online C Compiler and Editor */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_ROWS    10
#define NUM_COLS    8

struct output {
    int val;
    int finished;
    int visited;
};

int matrix[NUM_ROWS][NUM_COLS];
struct output out[NUM_ROWS][NUM_COLS] = {{{0}}};

void rand_matrix(void)
{
    int i, j;

    srand(time(0));

    for (i = 0; i < NUM_ROWS; i++)
        for (j = 0; j < NUM_COLS; j++)
            matrix[i][j] = rand() % 2;
}

void print_matrix(void)
{
    int i, j;
    
    for (i = 0; i < NUM_ROWS; i++) {
        for (j = 0; j < NUM_COLS; j++) {
            printf("%d ", matrix[i][j]);
        }
        
        printf("\n");
    }
}

void set_output(void)
{
    int i, j;
    
    for (i = 0; i < NUM_ROWS; i++)
        for (j = 0; j < NUM_COLS; j++)
            out[i][j].val = -1;
}

void print_output(void)
{
    int i, j;
    
    for (i = 0; i < NUM_ROWS; i++) {
        for (j = 0; j < NUM_COLS; j++) {
            printf("%d ", out[i][j].val);
        }
        
        printf("\n");
    }
}

int is_border(int i, int j)
{
    return i == 0 || j == 0 || i == NUM_ROWS-1 ||
            j == NUM_COLS-1; 
}

int calc_val(int i, int j)
{
    int res;

    if (!matrix[i][j])
        return 0;

    if (is_border(i, j))
        return 1;

    if (out[i][j].visited)
        return 0;

    out[i][j].visited = 1;

    res = calc_val(i-1,j) || calc_val(i,j-1) ||
            calc_val(i+1,j) || calc_val(i,j+1);
            
    out[i][j].visited = 0;

    return res;
}

void remove_islands(void)
{
    int i, j;

    for (i = 0 ; i < NUM_ROWS; i++)
        for (j = 0 ; j < NUM_COLS; j++)
            out[i][j].val = calc_val(i, j);
}

int main()
{
    rand_matrix();
    printf("Matrix\n");
    print_matrix();
    set_output();
    remove_islands();
    printf("\n");
    printf("Output\n");
    print_output();

    return 0;
}