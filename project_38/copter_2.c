#define _XOPEN_SOURCE_EXTENDED
#include <locale.h>
#include <ncurses.h>
#include <wchar.h>
#include <ncursesw/ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <locale.h>
#include <wchar.h>

#define STAR_COUNT 200
#define MAX_LEN_RATIO 0.7
#define MAX_VELOCITY 0.6
#define GRAVITY 0.05
#define LIFT -0.8

typedef struct {
    int x, y;
    int type;
    int speed;
    int color;
} Star;

Star stars[STAR_COUNT];

float velocity = 0;
float b_y_pos;
int b_x_pos;
int o_x_pos, o_y_pos, len;
int term_rows, term_cols;
int quit = 0;

int score = 0;
int high_score = 0;
int scored = 0;

int speed_level = 1;
int obstacle_speed = 1;
int target_fps = 60;
long long frame_time_ns;

long long current_time_ns() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (long long)ts.tv_sec * 1000000000LL + ts.tv_nsec;
}

void rand_obstacle() {
    int max_len = (int)(term_rows * MAX_LEN_RATIO);
    len = 5 + rand() % (max_len - 5);

    // Bias toward bottom: use a weighted random
    float bias = (float)(rand() % 100) / 100.0;
    bias = bias * bias;  // Squared to skew toward 0 (bottom)

    int available_space = term_rows - 4 - len;
    o_y_pos = 2 + (int)(bias * available_space);

    o_x_pos = term_cols - 11;
    scored = 0;
}

int is_crash() {
    int by = (int)b_y_pos;

    // Collision with vertical obstacle
    if (b_x_pos == o_x_pos && by >= o_y_pos && by < o_y_pos + len) return 1;
    if (b_x_pos == o_x_pos + 1 && by >= o_y_pos - 1 && by < o_y_pos + len + 1) return 1;

    // Collision with floor
    if (by >= term_rows - 2) return 1;

    return 0;
}

void init_stars() {
    for (int i = 0; i < STAR_COUNT; i++) {
        stars[i].x = rand() % (term_cols - 2) + 1;
        stars[i].y = rand() % (term_rows - 2) + 1;
        stars[i].type = rand() % 3;
        stars[i].speed = 1 + rand() % 3;
        stars[i].color = 1 + rand() % 4;
    }
}

void update_stars() {
    for (int i = 0; i < STAR_COUNT; i++) {
        stars[i].x -= stars[i].speed;
        if (stars[i].x < 1) {
            stars[i].x = term_cols - 2;
            stars[i].y = rand() % (term_rows - 2) + 1;
            stars[i].type = rand() % 3;
            stars[i].speed = 1 + rand() % 3;
            stars[i].color = 1 + rand() % 4;
        }
    }
}

void draw_scene() {
    erase();
    box(stdscr, 0, 0);

    // Draw stars
    for (int i = 0; i < STAR_COUNT; i++) {
        if (rand() % 5 == 0) continue;
        int pair = stars[i].color;
        if (pair < 1 || pair > 4) pair = 2;
        attron(COLOR_PAIR(pair));
        char ch = (stars[i].type == 0) ? '.' : (stars[i].type == 1) ? '*' : '+';
        mvaddch(stars[i].y, stars[i].x, ch);
        attroff(COLOR_PAIR(pair));
    }

    // Draw plane using wide characters
    int by = (int)b_y_pos;
    wchar_t plane[] = L"✈";
    attron(COLOR_PAIR(5));
    mvaddwstr(by, b_x_pos - 1, plane);
    attroff(COLOR_PAIR(5));

    // Draw obstacle
    attron(COLOR_PAIR(6) | A_BOLD);
    for (int i = 0; i < len; i++) {
        if (o_y_pos + i < term_rows - 1)
            mvaddch(o_y_pos + i, o_x_pos, ACS_CKBOARD);
    }
    attroff(COLOR_PAIR(6) | A_BOLD);

    // Draw score
    attron(COLOR_PAIR(7));
    mvprintw(1, 2, "Score: %d", score);
    mvprintw(2, 2, "High Score: %d", high_score);
    attroff(COLOR_PAIR(7));

    doupdate();
}

void choose_speed() {
    erase();
    attron(COLOR_PAIR(7));
    mvprintw(5, 5, "Choose speed:");
    mvprintw(7, 7, "1 - Slow");
    mvprintw(8, 7, "2 - Medium");
    mvprintw(9, 7, "3 - Fast");
    attroff(COLOR_PAIR(7));
    refresh();

    int ch;
    while (1) {
        ch = getch();
        if (ch == '1') {
            speed_level = 0;
            target_fps = 30;
            obstacle_speed = 1;
            break;
        } else if (ch == '2') {
            speed_level = 1;
            target_fps = 60;
            obstacle_speed = 1;
            break;
        } else if (ch == '3') {
            speed_level = 2;
            target_fps = 90;
            obstacle_speed = 2;
            break;
        }
    }

    frame_time_ns = 1000000000 / target_fps;
}

void game_over_screen() {
    erase();
    attron(COLOR_PAIR(8) | A_BOLD);
    mvprintw(term_rows / 2 - 1, term_cols / 2 - 5, "GAME OVER!");
    attroff(COLOR_PAIR(8) | A_BOLD);
    refresh();
    usleep(2000000);
}

void load_high_score() {
    FILE *f = fopen("highscore.txt", "r");
    if (f) {
        fscanf(f, "%d", &high_score);
        fclose(f);
    } else {
        high_score = 0;
    }
}

void save_high_score() {
    if (score > high_score) {
        FILE *f = fopen("highscore.txt", "w");
        if (f) {
            fprintf(f, "%d\n", score);
            fclose(f);
        }
    }
}

void countdown() {
    erase();
    attron(COLOR_PAIR(7) | A_BOLD);
    for (int i = 3; i >= 1; i--) {
        mvprintw(term_rows / 2, term_cols / 2 - 2, "%d...", i);
        refresh();
        usleep(1000000);  // 1 second
        erase();
    }
    mvprintw(term_rows / 2, term_cols / 2 - 4, "GO!");
    refresh();
    usleep(800000);  // Slight pause before game starts
    attroff(COLOR_PAIR(7) | A_BOLD);
}

int main() {
    setlocale(LC_ALL, "");  // Enable UTF-8 support

    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    if (!has_colors()) {
        endwin();
        printf("Your terminal does not support color.\n");
        return 1;
    }

    start_color();
    use_default_colors();
    init_pair(1, COLOR_YELLOW, -1);
    init_pair(2, COLOR_CYAN, -1);
    init_pair(3, COLOR_MAGENTA, -1);
    init_pair(4, COLOR_WHITE, -1);
    init_pair(5, COLOR_GREEN, -1);   // Plane
    init_pair(6, COLOR_RED, -1);     // Obstacle
    init_pair(7, COLOR_WHITE, -1);   // UI
    init_pair(8, COLOR_MAGENTA, -1); // Game Over

    getmaxyx(stdscr, term_rows, term_cols);
    if (term_rows < 20 || term_cols < 40) {
        endwin();
        printf("Terminal too small. Resize to at least 20x40.\n");
        return 1;
    }

    choose_speed();
    load_high_score();
    srand(time(NULL));
    b_x_pos = term_cols / 6;
    b_y_pos = term_rows / 2;
    rand_obstacle();
    init_stars();

    countdown();

    while (!quit) {
        long long start = current_time_ns();

        int ch = getch();
        if (ch == KEY_UP) {
            velocity = (velocity > 0.2) ? LIFT * 1.5 : LIFT;
        } else if (ch == 'q') {
            quit = 1;
        }

        velocity += GRAVITY;
        if (velocity > MAX_VELOCITY) velocity = MAX_VELOCITY;
        if (velocity < -MAX_VELOCITY) velocity = -MAX_VELOCITY;

        b_y_pos += velocity;
        if (b_y_pos < 2) {
            b_y_pos = 2;
        velocity = 0;
        }
        if (b_y_pos > term_rows - 2) {
            b_y_pos = term_rows - 2;
            velocity = 0;
        }

        o_x_pos -= obstacle_speed;
        if (o_x_pos < 1) {
            rand_obstacle();
        }

        // Scoring logic
        if (o_x_pos + 1 == b_x_pos && !scored) {
            score++;
            scored = 1;
        }

        if (is_crash()) {
            save_high_score();
            game_over_screen();
            break;
        }

        update_stars();
        draw_scene();

        long long end = current_time_ns();
        long long elapsed = end - start;
        if (elapsed < frame_time_ns) {
            usleep((frame_time_ns - elapsed) / 1000);
        }
    }

    endwin();
    return 0;
}