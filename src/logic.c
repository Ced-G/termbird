#include "logic.h"

enum CollisionType detect_collision(Bird *bird, PipeList *pl, int max_y) {
  if (bird->y < 0 || bird->y > max_y)
    return COLLIDE;

  for (Pipe *p = pl->first; p; p = p->next) {
    if (p->x > bird->x)
      break;

    if (bird->x >= p->x && bird->x <= p->x + PIPE_WIDTH) {
      if (bird->y > p->gap_y + PIPE_GAP || bird->y < p->gap_y - PIPE_GAP)
        return COLLIDE;
      else if (bird->x == p->x + PIPE_WIDTH)
        return SCORE;
    }
  }

  return SAFE;
}
