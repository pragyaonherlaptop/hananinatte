#ifndef RETRO_H
#define RETRO_H

#include <stdbool.h>
#include "raylib.h"

#define RETRO_FACE     ((Color){ 192, 192, 192, 255 })
#define RETRO_LIGHT    ((Color){ 223, 223, 223, 255 })
#define RETRO_DARK     ((Color){ 128, 128, 128, 255 })
#define RETRO_WHITE    ((Color){ 255, 255, 255, 255 })
#define RETRO_BLACK    ((Color){   0,   0,   0, 255 })
#define RETRO_DESKTOP  ((Color){   0, 128, 128, 255 })
#define RETRO_NAVY     ((Color){   0,   0, 128, 255 })
#define RETRO_SKY      ((Color){  16, 132, 208, 255 })

typedef enum { FACE_HAPPY, FACE_DEAD, FACE_COOL } FaceMood;

void retro_bevel(int x, int y, int w, int h, bool sunken);
void retro_draw_window(void);
void retro_draw_taskbar(void);
void retro_draw_status(const char *left, const char *right);
void retro_draw_lcd(int x, int y, int value);
void retro_draw_face(int x, int y, FaceMood mood);
void retro_message_box(const char *title, const char *line1,
                       const char *line2, bool isError);

#endif
