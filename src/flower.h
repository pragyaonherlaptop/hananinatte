#ifndef FLOWER_H
#define FLOWER_H

#include "raylib.h"

typedef enum {
    FLOWER_RED,
    FLOWER_YELLOW,
    FLOWER_PINK,
    FLOWER_BLUE,
    FLOWER_WHITE,
    FLOWER_TYPE_COUNT
} FlowerType;

typedef struct {
    const char *name;
    Color petal;
    Color center;
} FlowerInfo;

const FlowerInfo *flower_info(int type);
void flower_draw(int px, int py, FlowerType type);

#endif
