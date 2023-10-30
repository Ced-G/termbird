#ifndef LOGIC_H
#define LOGIC_H

#include "bird.h"
#include "pipe.h"

enum CollisionType {
    COLLIDE,
    SAFE,
    SCORE
};

enum CollisionType detect_collision(Bird *bird, PipeList *pl, int max_y);

#endif // LOGIC_H
