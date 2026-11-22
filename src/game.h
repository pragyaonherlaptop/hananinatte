#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include "config.h"
#include "snake.h"
#include "flower.h"

typedef enum {
    STATE_PLAYING,
    STATE_PAUSED,
    STATE_GAME_OVER,
    STATE_WON
} GameState;

typedef struct {
    Point pos;
    FlowerType type;
} Flower;

typedef struct {
    Snake snake;
    Flower flowers[FLOWERS_ON_FIELD];
    int lastAte;        /* flower type last eaten, -1 = none yet */
    int score;
    int highScore;
    float timer;
    GameState state;
} Game;

void game_init(Game *g);
void game_reset(Game *g);
void game_handle_input(Game *g);
void game_update(Game *g, float dt);
void game_draw(const Game *g);

#endif
