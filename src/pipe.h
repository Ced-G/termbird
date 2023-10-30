#ifndef PIPE_H
#define PIPE_H

#include <ncurses.h>

#define PIPE_WIDTH 8
#define PIPE_GAP 6

struct Pipe
{
    int x;
    int gap_y;
    struct Pipe *next;
};
typedef struct Pipe Pipe;

struct PipeList
{
    struct Pipe *first;
    struct Pipe *last;
};
typedef struct PipeList PipeList;

PipeList *init_pipe_list();

void destroy_pipe_list(PipeList *pl);

void clean_pipes(PipeList *pl);

void *advance_pipes(PipeList *pl);

void *draw_pipes(WINDOW *win, int max_x, PipeList *pl);

Pipe *init_pipe(PipeList *pl, int screen_width, int screen_height);

void draw_pipe(WINDOW *win, int max_x, Pipe *pipe);

#endif // PIPE_H
