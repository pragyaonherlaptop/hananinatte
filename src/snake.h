#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>
#include "config.h"

typedef struct {
    int x;
    int y;
} Point;

typedef enum {
    DIR_UP,
    DIR_DOWN,
    DIR_LEFT,
    DIR_RIGHT
} Direction;

typedef struct {
    Point body[MAX_SNAKE];  /* body[0] is the head */
    int   tint[MAX_SNAKE];  /* flower type absorbed by segment, -1 = plain */
    int   length;
    Direction dir;          /* direction used for the last move */
    Direction nextDir;      /* direction queued from input */
} Snake;

void  snake_init(Snake *s);
void  snake_set_direction(Snake *s, Direction d);
Point snake_next_head(const Snake *s);
bool  snake_occupies(const Snake *s, Point p, bool ignoreTail);
void  snake_move(Snake *s, Point newHead, bool grow, int tint);

#endif
