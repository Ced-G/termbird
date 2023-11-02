#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "bird.h"
#include "pipe.h"
#include "logic.h"
#include <time.h>

struct game_settings {
    int pipe_interval;
    int speed;
    int score;
} settings = { .pipe_interval = 50, .speed = 1, .score = 0 };

void game_over_screen(int score, int max_x, int max_y)
{
    char *msg = "Game Over!";
    char scoreStr[50];
    sprintf(scoreStr, "Your Score: %d", score);

    int starty = (max_y - 2) / 2;
    int startx_msg = (max_x - strlen(msg)) / 2;
    int startx_score = (max_x - strlen(scoreStr)) / 2;

    clear();
    mvprintw(starty, startx_msg, "%s", msg);
    mvprintw(starty + 1, startx_score, "%s", scoreStr);
    refresh();

    getch();
}

void display_score(WINDOW *win, int score, int max_x, int max_y)
{
    char scoreStr[50];
    sprintf(scoreStr, "Score: %d", score);
    int len = strlen(scoreStr);
    int startx_score = (max_x - strlen(scoreStr)) / 2;

    mvwprintw(win, 2, startx_score, "%s", scoreStr);
}

int main()
{	
    int ch;
    int max_x, max_y;
    int interval = 0;
    double speed = 30.;
    enum CollisionType collision;

	initscr();
    if (has_colors() == FALSE)
    {	endwin();
        printf("Your terminal does not support color\n");
        printf("No color mode not implemented yet :(\n");
        exit(1);
    }

    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(2, COLOR_BLACK, COLOR_GREEN);
	
	cbreak();
    keypad(stdscr, TRUE);
	noecho();
    curs_set(0);
    nodelay(stdscr, TRUE);

    Bird *bird = init_bird(20, 10);
    PipeList *pl = init_pipe_list();
    srand(time(NULL));

    getmaxyx(stdscr, max_y, max_x);
    WINDOW *next_frame = newwin(max_y, max_x, 0, 0);

    while (true)
    {
        clock_t start = clock();

        if (interval++ >= settings.pipe_interval)
        {
            init_pipe(pl, max_x, max_y);
            interval = 0;
        }

        werase(next_frame);

        ch = getch();
        if (ch == KEY_END)
            break;
        if (ch == ERR)
            update_position(bird, 0); 
        else
            update_position(bird, 1);

        draw_bird(next_frame, bird);
        draw_pipes(next_frame, max_x, pl);
        display_score(next_frame, settings.score, max_x, max_y);
        wrefresh(next_frame);
        
        collision = detect_collision(bird, pl, max_y);
        if (collision == COLLIDE) 
            break;
        else if (collision == SCORE)
        {
            settings.score++;
            if (settings.score % 10 == 0)
                speed += 1;
        }
        advance_pipes(pl);

        clock_t end = clock();
        double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;
        double time_to_sleep = (1.0 / speed) - elapsed_time; // 30 FPS
        if (time_to_sleep > 0) {
            usleep(time_to_sleep * 1000000); // usleep takes microseconds
        }
    }

    delwin(next_frame);

    nodelay(stdscr, false);
    game_over_screen(settings.score, max_x, max_y);

    endwin();
    destroy_pipe_list(pl);
    free(bird);
	return 0;
}
