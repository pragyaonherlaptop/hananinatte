#include <stdio.h>
#include <time.h>
#include "retro.h"
#include "config.h"

/* Raised or sunken 3D rectangle, like old Windows buttons and panels. */
void retro_bevel(int x, int y, int w, int h, bool sunken)
{
    Color oTL = sunken ? RETRO_DARK  : RETRO_WHITE;
    Color oBR = sunken ? RETRO_WHITE : RETRO_BLACK;
    Color iTL = sunken ? RETRO_BLACK : RETRO_LIGHT;
    Color iBR = sunken ? RETRO_FACE  : RETRO_DARK;

    DrawRectangle(x, y, w, h, RETRO_FACE);

    DrawRectangle(x, y, w - 1, 1, oTL);
    DrawRectangle(x, y, 1, h - 1, oTL);
    DrawRectangle(x, y + h - 1, w, 1, oBR);
    DrawRectangle(x + w - 1, y, 1, h, oBR);

    DrawRectangle(x + 1, y + 1, w - 3, 1, iTL);
    DrawRectangle(x + 1, y + 1, 1, h - 3, iTL);
    DrawRectangle(x + 1, y + h - 2, w - 2, 1, iBR);
    DrawRectangle(x + w - 2, y + 1, 1, h - 2, iBR);
}

static void title_bar(int x, int y, int w, const char *text, bool allButtons)
{
    DrawRectangleGradientH(x, y, w, 11, RETRO_NAVY, RETRO_SKY);

    /* tiny app icon */
    DrawRectangle(x + 2, y + 2, 7, 7, (Color){ 60, 200, 40, 255 });
    DrawRectangle(x + 4, y + 4, 3, 3, (Color){ 255, 120, 190, 255 });

    DrawText(text, x + 12, y + 1, 10, RETRO_WHITE);

    int r = x + w;
    int by = y + 1;

    /* close button (X) */
    int cx = r - 13;
    retro_bevel(cx, by, 11, 9, false);
    DrawLine(cx + 3, by + 2, cx + 8, by + 7, RETRO_BLACK);
    DrawLine(cx + 4, by + 2, cx + 9, by + 7, RETRO_BLACK);
    DrawLine(cx + 8, by + 2, cx + 3, by + 7, RETRO_BLACK);
    DrawLine(cx + 9, by + 2, cx + 4, by + 7, RETRO_BLACK);

    if (allButtons) {
        int mx = r - 26;
        retro_bevel(mx, by, 11, 9, false);
        DrawRectangle(mx + 2, by + 1, 7, 2, RETRO_BLACK);
        DrawRectangleLines(mx + 2, by + 1, 7, 7, RETRO_BLACK);

        int nx = r - 37;
        retro_bevel(nx, by, 11, 9, false);
        DrawRectangle(nx + 3, by + 6, 5, 2, RETRO_BLACK);
    }
}

void retro_draw_window(void)
{
    ClearBackground(RETRO_DESKTOP);

    retro_bevel(WIN_X, WIN_Y, WIN_W, WIN_H, false);
    title_bar(WIN_X + 3, WIN_Y + 3, WIN_W - 6, "Snake 95 - Flower Garden", true);

    DrawText("Game", WIN_X + 7,  WIN_Y + 16, 10, RETRO_BLACK);
    DrawText("Help", WIN_X + 38, WIN_Y + 16, 10, RETRO_BLACK);
}

void retro_draw_taskbar(void)
{
    int ty = VIRT_H - 16;
    retro_bevel(0, ty, VIRT_W, 16, false);

    /* Start button */
    retro_bevel(2, ty + 2, 40, 12, false);
    DrawRectangle(5,  ty + 4, 3, 3, (Color){ 255,  40,  40, 255 });
    DrawRectangle(9,  ty + 4, 3, 3, (Color){  40, 200,  40, 255 });
    DrawRectangle(5,  ty + 8, 3, 3, (Color){  40,  80, 255, 255 });
    DrawRectangle(9,  ty + 8, 3, 3, (Color){ 255, 220,   0, 255 });
    DrawText("Start", 15, ty + 3, 10, RETRO_BLACK);
    DrawText("Start", 16, ty + 3, 10, RETRO_BLACK);  /* fake bold */

    /* Pressed task button for our window */
    retro_bevel(46, ty + 2, 90, 12, true);
    DrawText("Snake 95", 52, ty + 3, 10, RETRO_BLACK);

    /* Clock */
    char buf[16] = "--:--";
    time_t t = time(NULL);
    struct tm *lt = localtime(&t);
    if (lt) {
        int h = lt->tm_hour % 12;
        if (h == 0) h = 12;
        snprintf(buf, sizeof(buf), "%d:%02d %s", h, lt->tm_min,
                 lt->tm_hour >= 12 ? "PM" : "AM");
    }
    retro_bevel(VIRT_W - 62, ty + 2, 60, 12, true);
    DrawText(buf, VIRT_W - 56, ty + 3, 10, RETRO_BLACK);
}

void retro_draw_status(const char *left, const char *right)
{
    int x = WIN_X + 3;
    int rightEdge = WIN_X + WIN_W - 3;

    retro_bevel(x, STATUS_Y, 180, STATUS_H, true);
    DrawText(left, x + 4, STATUS_Y + 2, 10, RETRO_BLACK);

    int rx = x + 182;
    retro_bevel(rx, STATUS_Y, rightEdge - rx, STATUS_H, true);
    DrawText(right, rx + 4, STATUS_Y + 2, 10, RETRO_BLACK);
}

void retro_draw_lcd(int x, int y, int value)
{
    char buf[8];
    if (value > 999) value = 999;
    snprintf(buf, sizeof(buf), "%03d", value);

    retro_bevel(x, y, LCD_W, LCD_H, true);
    DrawRectangle(x + 2, y + 2, LCD_W - 4, LCD_H - 4, RETRO_BLACK);
    DrawText(buf, x + 7, y + 3, 10, (Color){ 255, 0, 0, 255 });
}

void retro_draw_face(int x, int y, FaceMood mood)
{
    retro_bevel(x, y, FACE_SIZE, FACE_SIZE, false);

    int cx = x + FACE_SIZE / 2;
    int cy = y + FACE_SIZE / 2;

    DrawCircle(cx, cy, 6, (Color){ 255, 235, 0, 255 });
    DrawCircleLines(cx, cy, 6, RETRO_BLACK);

    if (mood == FACE_COOL) {
        DrawRectangle(cx - 4, cy - 2, 9, 2, RETRO_BLACK);
        DrawRectangle(cx - 2, cy + 2, 5, 1, RETRO_BLACK);
    } else if (mood == FACE_DEAD) {
        DrawLine(cx - 3, cy - 3, cx - 1, cy - 1, RETRO_BLACK);
        DrawLine(cx - 1, cy - 3, cx - 3, cy - 1, RETRO_BLACK);
        DrawLine(cx + 1, cy - 3, cx + 3, cy - 1, RETRO_BLACK);
        DrawLine(cx + 3, cy - 3, cx + 1, cy - 1, RETRO_BLACK);
        DrawRectangle(cx - 2, cy + 3, 5, 1, RETRO_BLACK);
    } else {
        DrawRectangle(cx - 3, cy - 2, 1, 2, RETRO_BLACK);
        DrawRectangle(cx + 2, cy - 2, 1, 2, RETRO_BLACK);
        DrawRectangle(cx - 3, cy + 1, 1, 1, RETRO_BLACK);
        DrawRectangle(cx - 2, cy + 2, 5, 1, RETRO_BLACK);
        DrawRectangle(cx + 3, cy + 1, 1, 1, RETRO_BLACK);
    }
}

void retro_message_box(const char *title, const char *line1,
                       const char *line2, bool isError)
{
    int w = 150, h = 64;
    int x = FIELD_X + (FIELD_W - w) / 2;
    int y = FIELD_Y + (FIELD_H - h) / 2;

    retro_bevel(x, y, w, h, false);
    title_bar(x + 3, y + 3, w - 6, title, false);

    /* Icon */
    int ix = x + 16, iy = y + 28;
    if (isError) {
        DrawCircle(ix, iy, 7, (Color){ 220, 0, 0, 255 });
        DrawLine(ix - 3, iy - 3, ix + 3, iy + 3, RETRO_WHITE);
        DrawLine(ix - 2, iy - 3, ix + 4, iy + 3, RETRO_WHITE);
        DrawLine(ix + 3, iy - 3, ix - 3, iy + 3, RETRO_WHITE);
        DrawLine(ix + 4, iy - 3, ix - 2, iy + 3, RETRO_WHITE);
    } else {
        DrawCircle(ix, iy, 7, (Color){ 0, 0, 200, 255 });
        DrawRectangle(ix - 1, iy - 4, 2, 2, RETRO_WHITE);
        DrawRectangle(ix - 1, iy - 1, 2, 5, RETRO_WHITE);
    }

    DrawText(line1, x + 30, y + 19, 10, RETRO_BLACK);
    DrawText(line2, x + 30, y + 30, 10, RETRO_BLACK);

    /* OK button */
    int bw = 44, bh = 14;
    int bx = x + (w - bw) / 2;
    int by = y + h - 19;
    DrawRectangleLines(bx - 1, by - 1, bw + 2, bh + 2, RETRO_BLACK);
    retro_bevel(bx, by, bw, bh, false);
    DrawRectangleLines(bx + 3, by + 3, bw - 6, bh - 6, RETRO_DARK);
    DrawText("OK", bx + (bw - MeasureText("OK", 10)) / 2, by + 2, 10, RETRO_BLACK);
}
