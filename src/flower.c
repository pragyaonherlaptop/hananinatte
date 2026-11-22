#include "flower.h"

static const FlowerInfo INFO[FLOWER_TYPE_COUNT] = {
    { "Red Poppy",    { 230,  20,  20, 255 }, { 255, 230,   0, 255 } },
    { "Yellow Daisy", { 255, 235,  20, 255 }, { 170,  90,   0, 255 } },
    { "Pink Tulip",   { 255, 120, 190, 255 }, { 255, 230,   0, 255 } },
    { "Blue Bell",    {  70, 120, 255, 255 }, { 255, 255, 255, 255 } },
    { "White Lily",   { 255, 255, 255, 255 }, { 255, 200,   0, 255 } },
};

/* 10x10 pixel sprite.  P = petal, C = center, S = stem, L = leaf */
static const char *SPRITE[10] = {
    "...PPPP...",
    "..PPPPPP..",
    ".PPPCCPPP.",
    ".PPCCCCPP.",
    ".PPCCCCPP.",
    ".PPPCCPPP.",
    "..PPPPPP..",
    "...PPPP...",
    "....SS....",
    "...LSS....",
};

const FlowerInfo *flower_info(int type)
{
    if (type < 0 || type >= FLOWER_TYPE_COUNT) type = 0;
    return &INFO[type];
}

void flower_draw(int px, int py, FlowerType type)
{
    const FlowerInfo *f = flower_info(type);
    Color stem = {   0,  70,   0, 255 };
    Color leaf = {  60, 200,  40, 255 };

    for (int r = 0; r < 10; r++) {
        for (int c = 0; c < 10; c++) {
            Color col;
            switch (SPRITE[r][c]) {
                case 'P': col = f->petal;  break;
                case 'C': col = f->center; break;
                case 'S': col = stem;      break;
                case 'L': col = leaf;      break;
                default:  continue;
            }
            DrawRectangle(px + c, py + r, 1, 1, col);
        }
    }
}
