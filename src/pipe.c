#include "pipe.h"
#include <stdlib.h>
#include <string.h>

PipeList *init_pipe_list() {
  PipeList *pl = malloc(sizeof(PipeList));
  pl->first = NULL;
  pl->last = NULL;

  return pl;
}

void destroy_pipe_list(PipeList *pl) {
  Pipe *p = pl->first;
  while (p) {
    Pipe *tmp = p;
    p = p->next;
    free(tmp);
  }

  free(pl);
}

void clean_pipes(PipeList *pl) {
  if (!pl->first || pl->first->x + PIPE_WIDTH > 0)
    return;

  Pipe *tmp = pl->first;
  pl->first = tmp->next;

  free(tmp);
}

void *advance_pipes(PipeList *pl) {
  for (Pipe *p = pl->first; p; p = p->next)
    p->x = p->x - 1;

  clean_pipes(pl);
}

void *draw_pipes(WINDOW *win, int max_x, PipeList *pl) {
  for (Pipe *p = pl->first; p && p->x < max_x; p = p->next)
    draw_pipe(win, max_x, p);
}

Pipe *init_pipe(PipeList *pl, int screen_width, int screen_height) {
  Pipe *pipe = malloc(sizeof(Pipe));
  pipe->x = screen_width + PIPE_WIDTH;
  pipe->gap_y = rand() % (screen_height - 10) + 5;
  pipe->next = NULL;

  if (!pl->first)
    pl->first = pipe;
  if (pl->last)
    pl->last->next = pipe;

  pl->last = pipe;

  return pipe;
}

void draw_pipe(WINDOW *win, int max_x, Pipe *pipe) {
  wattron(win, COLOR_PAIR(2));

  char str[PIPE_WIDTH];
  char strlim[PIPE_WIDTH];
  memset(str, ' ', PIPE_WIDTH - 1);
  memset(strlim, '_', PIPE_WIDTH - 1);
  str[PIPE_WIDTH - 1] = '\0';
  int x = pipe->x;

  if (pipe->x < 0) {
    str[PIPE_WIDTH + pipe->x] = '\0';
    strlim[PIPE_WIDTH + pipe->x] = '\0';
    x = 0;
  }

  if (pipe->x + PIPE_WIDTH > max_x) {
    str[max_x - x] = '\0';
    strlim[max_x - x] = '\0';
  }

  for (int i = 0; i < pipe->gap_y - PIPE_GAP; i++)
    mvwprintw(win, i, x, "%s", str);

  mvwprintw(win, pipe->gap_y - PIPE_GAP - 2, x, "%s", strlim);
  mvwprintw(win, pipe->gap_y + PIPE_GAP, x, "%s", strlim);

  for (int i = pipe->gap_y + PIPE_GAP + 1; i < LINES; i++)
    mvwprintw(win, i, x, "%s", str);

  wattroff(win, COLOR_PAIR(2));
}
