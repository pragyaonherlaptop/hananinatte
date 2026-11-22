#include "snake.h"

void snake_init(Snake *s)
{
    s->length = 3;
    s->dir = DIR_RIGHT;
    s->nextDir = DIR_RIGHT;

    int startX = GRID_W / 2;
    int startY = GRID_H / 2;

    for (int i = 0; i < s->length; i++) {
        s->body[i].x = startX - i;
        s->body[i].y = startY;
        s->tint[i] = -1;
    }
}

/* Queue a new direction, ignoring 180-degree reversals. */
void snake_set_direction(Snake *s, Direction d)
{
    if ((s->dir == DIR_UP    && d == DIR_DOWN)  ||
        (s->dir == DIR_DOWN  && d == DIR_UP)    ||
        (s->dir == DIR_LEFT  && d == DIR_RIGHT) ||
        (s->dir == DIR_RIGHT && d == DIR_LEFT)) {
        return;
    }
    s->nextDir = d;
}

Point snake_next_head(const Snake *s)
{
    Point p = s->body[0];

    switch (s->nextDir) {
        case DIR_UP:    p.y--; break;
        case DIR_DOWN:  p.y++; break;
        case DIR_LEFT:  p.x--; break;
        case DIR_RIGHT: p.x++; break;
    }
    return p;
}

/* If ignoreTail is true the last segment is skipped, since it moves away
   on a normal (non-growing) step. */
bool snake_occupies(const Snake *s, Point p, bool ignoreTail)
{
    int end = ignoreTail ? s->length - 1 : s->length;

    for (int i = 0; i < end; i++) {
        if (s->body[i].x == p.x && s->body[i].y == p.y) {
            return true;
        }
    }
    return false;
}

/* tint = flower type just eaten (used when grow is true), else -1.
   The color is stored at the head and slides down the body each step,
   like the snake is digesting the flower. */
void snake_move(Snake *s, Point newHead, bool grow, int tint)
{
    if (grow && s->length < MAX_SNAKE) {
        s->length++;
    }

    for (int i = s->length - 1; i > 0; i--) {
        s->body[i] = s->body[i - 1];
        s->tint[i] = s->tint[i - 1];
    }

    s->body[0] = newHead;
    s->tint[0] = grow ? tint : -1;
    s->dir = s->nextDir;
}
