#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

typedef unsigned char u8;

enum {
    EASY = 1,
    HARD
} mode;

char *mode_str[] = {
    [EASY] = "EASY",
    [HARD] = "HARD"
};

enum {
    VERY_SLOW = 1,
    SLOW,
    MEDIUM,
    FAST,
    VERY_FAST
} speed;

char *speed_str[] = {
    [VERY_SLOW] = "VERY SLOW",
    [SLOW] = "SLOW",
    [MEDIUM] = "MEDIUM",
    [FAST] = "FAST",
    [VERY_FAST] = "VERY FAST"
};

enum {
    RIGHT,
    LEFT,
    DOWN,
    UP
} dir, real_dir;

#define NUM_ROWS 30
#define NUM_COLS (NUM_ROWS * 2)
#define MAX_LEN 100

struct {
    char *buffer;
    int size;
    u8 row_size;
    u8 col_size;
} board;

char board2[NUM_ROWS + 2][NUM_COLS + 3] = {};

u8 len;
u8 x_pos[MAX_LEN];
u8 y_pos[MAX_LEN];

u8 c_x_pos;
u8 c_y_pos;

int waiting_us = 0;
int quit = 0;

static char get_input() {
    char buf, c;
    struct termios old = {0};
    struct termios new = {0};

    // Get current terminal settings
    tcgetattr(0, &old);

    // Create new settings based on old settings
    new = old;

    // Disable canonical mode and echo
    new.c_lflag &= ~(ICANON | ECHO);

    // Apply new settings
    tcsetattr(0, TCSANOW, &new);

    read(STDIN_FILENO, &buf, 1);
    if (buf == '\033') {
        read(STDIN_FILENO, &buf, 1);
        if (buf == '[') {
            read(STDIN_FILENO, &buf, 1);
            switch(buf) {
                case 'A': c = 'U'; break; // Up
                case 'B': c = 'D'; break; // Down
                case 'C': c = 'R'; break; // Right
                case 'D': c = 'L'; break; // Left
            }
        }
    } else {
        c = buf;
    }

    // Restore old settings
    tcsetattr(0, TCSANOW, &old);

    return c;
}

static void *thread_func()
{
    char c;

    do {
        c = get_input();

        if (c == 'D' && real_dir != UP)
            dir = DOWN;
        else if (c == 'U' && real_dir != DOWN)
            dir = UP;
        else if (c == 'L' && real_dir != RIGHT)
            dir = LEFT;
        else if (c == 'R' && real_dir != LEFT)
            dir = RIGHT;
    } while (c != 'q' && !quit);

    quit = 1;

    return NULL;
}

static void clear_screen()
{
    printf("\033[H\033[J");
}

int is_head(int x, int y)
{
    return x_pos[0] == x && y_pos[0] == y;
}

static int is_body(int x, int y)
{
    int i;

    for (i = 1; i < len; i++)
        if (x_pos[i] == x && y_pos[i] == y)
            return 1;

    return 0;
}

int is_candy(int x, int y)
{
    return c_x_pos == x && c_y_pos == y;
}

static void draw_board()
{
    char *buf = board.buffer;
    int i = 0, size = board.size;
    u8 row_size = board.row_size, col_size = board.col_size;
    int x, y;

    /* Clear the board */
    memset(buf, ' ', size);

    /* Fill upper border with |---| */
    buf[i++] = '|';
    while (i < row_size - 1)
        buf[i++] = '-';
    buf[i++] = '|';
    buf[i++] = '\n';

    /* Fill side boarders with | and the game board */
    while (i < (row_size + 1)*(col_size - 1)) {
        x = i % (row_size + 1);
        y = i / (row_size + 1);

        if (x == 0 || x == row_size-1)
            buf[i] = '|';
        else if (x == row_size)
            buf[i] = '\n';
        else if (is_head(x, y))
            buf[i] = 'O';
        else if (is_body(x, y))
            buf[i] = 'o';
        else if (is_candy(x, y))
            buf[i] = '*';

        i++;
    }

    /* Fill lower border with |---| */
    buf[i++] = '|';
    while (i < (row_size + 1)*(col_size - 1) + row_size - 1)
        buf[i++] = '-';
    buf[i++] = '|';
    buf[i++] = '\n';

    /* Make it a string */
    buf[i] = '\0';

    /* clear the screen before printing the new board */
    clear_screen();

    /* Print the board to the screen */
    printf("%s", buf);
    fflush(stdout);
}

static void move()
{
    u8 h_x_pos = x_pos[0];
    u8 h_y_pos = y_pos[0];

    if (dir == RIGHT) {
        real_dir = RIGHT;

        if (h_x_pos <= NUM_COLS - 3)
            h_x_pos += 2;
        else if (mode == EASY)
            h_x_pos = 1;
        else
            quit = 1;
    } else if (dir == LEFT) {
        real_dir = LEFT;

        if (h_x_pos >= 3)
            h_x_pos -= 2;
        else if (mode == EASY)
            h_x_pos = NUM_COLS - 1;
        else
            quit = 1;
    } else if (dir == DOWN) {
        real_dir = DOWN;

        if (h_y_pos <= NUM_ROWS-1)
            h_y_pos++;
        else if (mode == EASY)
            h_y_pos = 1;
        else
            quit = 1;
    } else if (dir == UP) {
        real_dir = UP;

        if (h_y_pos >= 2)
            h_y_pos--;
        else if (mode == EASY)
            h_y_pos = NUM_ROWS;
        else
            quit = 1;
    }

    if (quit == 1)
        return;

    if (is_body(h_x_pos, h_y_pos)) {
        quit = 1;
        return;
    }

    for (int i = len-1; i > 0; i--) {
        x_pos[i] = x_pos[i-1];
        y_pos[i] = y_pos[i-1];
    }

    x_pos[0] = h_x_pos;
    y_pos[0] = h_y_pos;
}

#define MAKE_ODD(x)    ((x) % 2 == 0 ? (x)+1 : (x))

static void rand_c_pos()
{
    u8 tmp_c_x_pos, tmp_c_y_pos;

    /* make sure that the new position of the candy isn't the snake position */
    while(1) {
        tmp_c_x_pos = rand() % NUM_COLS;
        tmp_c_x_pos = MAKE_ODD(tmp_c_x_pos);
        tmp_c_y_pos = 1 + (rand() % NUM_ROWS);

        if (!is_head(tmp_c_x_pos, tmp_c_y_pos) && !is_body(tmp_c_x_pos, tmp_c_y_pos))
            break;
    }

    c_x_pos = tmp_c_x_pos;
    c_y_pos = tmp_c_y_pos;
}

static void check_hit()
{
    if (x_pos[0] != c_x_pos || y_pos[0] != c_y_pos)
        return;

    len++;

    rand_c_pos();
}

static void init_board()
{
    board.row_size = NUM_COLS + 2;
    board.col_size = NUM_ROWS + 2;
    board.size = (board.row_size + 1) * board.col_size + 1;
    board.buffer = malloc(board.size * sizeof(char));
}

static void free_board()
{
    free(board.buffer);
}

static void init_params()
{
    u8 time_before_start_s = 3;
    char c;

    srand(time(NULL));
    rand_c_pos();

    x_pos[0] = 1;
    y_pos[0] = 1;
    len = 1;

    printf("Choose a mode: 1 - EASY (pass through the walls), 2 - HARD (can't touch the walls)\n");
    while(1) {
        c = get_input();
        switch (c) {
            case '1': mode = EASY; break;
            case '2': mode = HARD; break;
            default: break;
        }
        
        if (mode >= EASY)
            break;
        else
            printf("Invalid input - please type again...\n");
    }

    printf("\nChoose a speed from 1 to 5 (1 is the slowest, 5 is the fastest)\n");
    while(1) {
        c = get_input();
        switch (c) {
        case '1': speed = VERY_SLOW; waiting_us = 300000; break;
        case '2': speed = SLOW; waiting_us = 250000; break;
        case '3': speed = MEDIUM; waiting_us = 200000; break;
        case '4': speed = FAST; waiting_us = 150000; break;
        case '5': speed = VERY_FAST; waiting_us = 100000; break;
        default: break;
        }

        if (speed >= VERY_SLOW)
            break;
        else
            printf("Invalid input - please type again...\n");
    }

    printf("\nStarting the game in %u seconds, mode %s and speed %s. to quit, press 'q'\n",
            time_before_start_s, mode_str[mode], speed_str[speed]);

    printf("\n");
    while (time_before_start_s) {
        printf("%d", time_before_start_s);
        fflush(stdout);
        usleep(1000000);
        time_before_start_s--;
        printf("...");
        fflush(stdout);
    }
}

int main()
{
    pthread_t thread;

    clear_screen();

    init_board();
    init_params();
    pthread_create(&thread, NULL, thread_func, NULL);

    while(!quit) {
        draw_board();
        move();
        check_hit();
        usleep(waiting_us);
    }

    printf("GAME IS OVER!!!\n");

    pthread_join(thread, NULL);
    free_board();

    return 0;
}
