#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>

typedef unsigned char u8;

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

#define NUM_ROWS 30
#define NUM_COLS (NUM_ROWS * 2)
#define MAX_LEN 15

struct {
    char *buffer;
    int size;
    u8 row_size;
    u8 col_size;
} board;

u8 len;
u8 o_x_pos;
u8 o_y_pos;
u8 b_x_pos;
u8 b_y_pos;

int waiting_us = 0;
int quit = 0;

pthread_mutex_t lock;

static char get_input() {
    char buf, c = ' ';
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
            if (buf == 'A')
                c = 'U';
        }
    } else {
        c = buf;
    }

    // Restore old settings
    tcsetattr(0, TCSANOW, &old);

    return c;
}

static void *thread1_func()
{
    char c;

    do {
        pthread_mutex_lock(&lock);
        if (b_y_pos < NUM_ROWS-1)
            b_y_pos++;
        pthread_mutex_unlock(&lock);

        usleep(100000);
    } while (!quit);

    return NULL;
}

static void *thread2_func()
{
    char c;

    do {
        c = get_input();

        pthread_mutex_lock(&lock);
        if (c == 'U')
            if (b_y_pos > 2)
                b_y_pos--;
        pthread_mutex_unlock(&lock);
    } while (c != 'q' && !quit);

    quit = 1;

    return NULL;
}

static void clear_screen()
{
    printf("\033[H\033[J");
}

static int is_body(int x, int y)
{
    if (x == b_x_pos && y == b_y_pos)
        return 1;

    if (x == b_x_pos-1 && (y == b_y_pos || y == b_y_pos-1 || y == b_y_pos+1))
        return 1;

    return 0;
}

int is_obstacle(int x, int y)
{
    int i;

    for (i = 0; i < len; i++)
        if ((o_x_pos == x) && (o_y_pos + i == y))
            return 1;

    return 0;
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
        else if (is_body(x, y))
            buf[i] = '*';
        else if (is_obstacle(x, y))
            buf[i] = '|';

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

static int is_crash()
{
    if (b_x_pos == o_x_pos && b_y_pos >= o_y_pos && b_y_pos < o_y_pos + len)
        return 1;

    if (b_x_pos == o_x_pos+1 && b_y_pos >= o_y_pos-1 && b_y_pos < o_y_pos+len+1)
        return 1;

    return 0;
}

static void move()
{
    pthread_mutex_lock(&lock);

    o_x_pos--;

    if (is_crash())
        quit = 1;

    pthread_mutex_unlock(&lock);
}

static void rand_obstacle()
{
    len = 5 + rand() % MAX_LEN;
    o_y_pos = rand() % (NUM_ROWS + 1 - len);
    o_x_pos = NUM_COLS - 11;
}

static void check_pass()
{
    if (!o_x_pos)
        rand_obstacle();
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

    b_x_pos = 10;
    b_y_pos = NUM_ROWS / 2;
    
    rand_obstacle();

    printf("\nChoose a speed from 1 to 5 (1 is the slowest, 5 is the fastest)\n");
    while(1) {
        c = get_input();
        switch (c) {
        case '1': speed = VERY_SLOW; waiting_us = 150000; break;
        case '2': speed = SLOW; waiting_us = 120000; break;
        case '3': speed = MEDIUM; waiting_us = 100000; break;
        case '4': speed = FAST; waiting_us = 70000; break;
        case '5': speed = VERY_FAST; waiting_us = 50000; break;
        default: break;
        }

        if (speed >= VERY_SLOW)
            break;
        else
            printf("Invalid input - please type again...\n");
    }

    printf("\nStarting the game in %u second, speed %s. to quit, press 'q'\n",
            time_before_start_s, speed_str[speed]);

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
    pthread_t thread1, thread2;

    clear_screen();

    init_board();
    init_params();

    pthread_mutex_init(&lock, NULL);
    pthread_create(&thread1, NULL, thread1_func, NULL);
    pthread_create(&thread2, NULL, thread2_func, NULL);


    while(!quit) {
        draw_board();
        move();
        check_pass();
        usleep(waiting_us);
    }

    printf("GAME IS OVER!!!\n");

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    free_board();

    return 0;
}
