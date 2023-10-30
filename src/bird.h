#ifndef BIRD_H
#define BIRD_H

#include <ncurses.h>
#include <stdlib.h>

#define LIFT_POWER 2
#define GRAVITY 0.10

struct Bird {
    int x;
    int y;
    float lift;
};
typedef struct Bird Bird;

Bird *init_bird(int x, int y);

void update_position(Bird *bird, int fly);

void draw_bird(WINDOW *win, Bird *bird);

#endif // BIRD_H
