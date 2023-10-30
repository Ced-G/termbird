#include "bird.h"

Bird *init_bird(int x, int y) {
  Bird *bird = malloc(sizeof(Bird));

  bird->x = x;
  bird->y = y;
  bird->lift = 0;

  return bird;
}

void update_position(Bird *bird, int fly) {
  if (fly)
    bird->lift = LIFT_POWER;
  else {
    if (bird->lift > 0)
      bird->lift = (int)bird->lift - GRAVITY * 2;
    else
      bird->lift -= (bird->lift == 0 ? 1 : GRAVITY);
  }
  bird->y = (int)(bird->y - bird->lift);
}

void draw_bird(WINDOW *win, Bird *bird) {
  wattron(win, COLOR_PAIR(1));
  mvwprintw(win, bird->y, bird->x - 1, "  ");
  wattroff(win, COLOR_PAIR(1));
}
