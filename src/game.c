#include <stdio.h>
#include "raylib.h"
#include "game.h"
#include "retro.h"

#define LAWN_A ((Color){   0, 120,   0, 255 })
#define LAWN_B ((Color){   0, 104,   0, 255 })
#define SNAKE_HEAD ((Color){ 210, 255,  80, 255 })
#define SNAKE_BODY ((Color){ 130, 230,   0, 255 })

/*helpers*/

static bool flower_at(const Game *g, Point p, int ignoreIndex)
{
    for (int i = 0; i < FLOWERS_ON_FIELD; i++) {
        if (i == ignoreIndex) continue;
        if (g->flowers[i].pos.x == p.x && g->flowers[i].pos.y == p.y) {
            return true;
        }
    }
    return false;
}

static void spawn_flower(Game *g, int i)
{
    Point p;
    do {
        p.x = GetRandomValue(0, GRID_W - 1);
        p.y = GetRandomValue(0, GRID_H - 1);
    } while (snake_occupies(&g->snake, p, false) || flower_at(g, p, i));

    g->flowers[i].pos = p;
    g->flowers[i].type = (FlowerType)GetRandomValue(0, FLOWER_TYPE_COUNT - 1);
}

/*lifecycle*/

void game_init(Game *g)
{
    g->highScore = 0;
    game_reset(g);
}

void game_reset(Game *g)
{
    snake_init(&g->snake);
    g->score = 0;
    g->lastAte = -1;
    g->timer = 0.0f;
    g->state = STATE_PLAYING;

    for (int i = 0; i < FLOWERS_ON_FIELD; i++) {
        g->flowers[i].pos.x = -1;
        g->flowers[i].pos.y = -1;
    }
    for (int i = 0; i < FLOWERS_ON_FIELD; i++) {
        spawn_flower(g, i);
    }
}

/*input*/

void game_handle_input(Game *g)
{
    /* Clicking the smiley restarts, just like Minesweeper. */
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        int mx = GetMouseX() / SCALE;
        int my = GetMouseY() / SCALE;
        if (mx >= FACE_X && mx < FACE_X + FACE_SIZE &&
            my >= FACE_Y && my < FACE_Y + FACE_SIZE) {
            game_reset(g);
            return;
        }
    }

    if (g->state == STATE_GAME_OVER || g->state == STATE_WON) {
        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
            game_reset(g);
        }
        return;
    }

    if (IsKeyPressed(KEY_P)) {
        g->state = (g->state == STATE_PLAYING) ? STATE_PAUSED : STATE_PLAYING;
        return;
    }
    if (g->state == STATE_PAUSED) return;

    if (IsKeyPressed(KEY_UP)    || IsKeyPressed(KEY_W)) snake_set_direction(&g->snake, DIR_UP);
    if (IsKeyPressed(KEY_DOWN)  || IsKeyPressed(KEY_S)) snake_set_direction(&g->snake, DIR_DOWN);
    if (IsKeyPressed(KEY_LEFT)  || IsKeyPressed(KEY_A)) snake_set_direction(&g->snake, DIR_LEFT);
    if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) snake_set_direction(&g->snake, DIR_RIGHT);
}

/*update*/

void game_update(Game *g, float dt)
{
    if (g->state != STATE_PLAYING) return;

    g->timer += dt;
    if (g->timer < MOVE_INTERVAL) return;
    g->timer -= MOVE_INTERVAL;

    Point next = snake_next_head(&g->snake);

    /* Wall collision */
    if (next.x < 0 || next.x >= GRID_W || next.y < 0 || next.y >= GRID_H) {
        g->state = STATE_GAME_OVER;
        return;
    }

    /* Did we reach a flower? */
    int eaten = -1;
    for (int i = 0; i < FLOWERS_ON_FIELD; i++) {
        if (g->flowers[i].pos.x == next.x && g->flowers[i].pos.y == next.y) {
            eaten = i;
            break;
        }
    }

    /* Self collision (tail moves away unless we are growing) */
    if (snake_occupies(&g->snake, next, eaten < 0)) {
        g->state = STATE_GAME_OVER;
        return;
    }

    int tint = (eaten >= 0) ? (int)g->flowers[eaten].type : -1;
    snake_move(&g->snake, next, eaten >= 0, tint);

    if (eaten >= 0) {
        g->score++;
        g->lastAte = tint;
        if (g->score > g->highScore) g->highScore = g->score;

        if (g->snake.length >= WIN_LENGTH) {
            g->state = STATE_WON;
            return;
        }
        spawn_flower(g, eaten);
    }
}

/*drawing*/

static void draw_snake_segment(const Snake *s, int i)
{
    int x = FIELD_X + s->body[i].x * CELL_SIZE;
    int y = FIELD_Y + s->body[i].y * CELL_SIZE;

    Color c = SNAKE_BODY;
    if (i == 0) {
        c = SNAKE_HEAD;
    } else if (s->tint[i] >= 0) {
        c = flower_info(s->tint[i])->petal;
    }

    DrawRectangle(x, y, CELL_SIZE, CELL_SIZE, RETRO_BLACK);
    DrawRectangle(x + 1, y + 1, CELL_SIZE - 2, CELL_SIZE - 2, c);

    if (i == 0) {
        int e1x, e1y, e2x, e2y;
        switch (s->dir) {
            case DIR_UP:    e1x = 2; e1y = 2; e2x = 6; e2y = 2; break;
            case DIR_DOWN:  e1x = 2; e1y = 6; e2x = 6; e2y = 6; break;
            case DIR_LEFT:  e1x = 2; e1y = 2; e2x = 2; e2y = 6; break;
            default:        e1x = 6; e1y = 2; e2x = 6; e2y = 6; break;
        }
        DrawRectangle(x + e1x, y + e1y, 2, 2, RETRO_BLACK);
        DrawRectangle(x + e2x, y + e2y, 2, 2, RETRO_BLACK);
    }
}

void game_draw(const Game *g)
{
    retro_draw_window();

    /*score panel*/
    retro_bevel(WIN_X + 3, HUD_Y, WIN_W - 6, HUD_H, true);
    retro_draw_lcd(LCD_L_X, LCD_Y, g->score);
    retro_draw_lcd(LCD_R_X, LCD_Y, g->highScore);

    FaceMood mood = FACE_HAPPY;
    if (g->state == STATE_GAME_OVER) mood = FACE_DEAD;
    if (g->state == STATE_WON)       mood = FACE_COOL;
    retro_draw_face(FACE_X, FACE_Y, mood);

    /*lawn (two-tone checker)*/
    retro_bevel(FIELD_X - 2, FIELD_Y - 2, FIELD_W + 4, FIELD_H + 4, true);
    for (int y = 0; y < GRID_H; y++) {
        for (int x = 0; x < GRID_W; x++) {
            DrawRectangle(FIELD_X + x * CELL_SIZE, FIELD_Y + y * CELL_SIZE,
                          CELL_SIZE, CELL_SIZE, ((x + y) & 1) ? LAWN_A : LAWN_B);
        }
    }

    /*flowers*/
    for (int i = 0; i < FLOWERS_ON_FIELD; i++) {
        flower_draw(FIELD_X + g->flowers[i].pos.x * CELL_SIZE,
                    FIELD_Y + g->flowers[i].pos.y * CELL_SIZE,
                    g->flowers[i].type);
    }

    /*snake (tail first so the head is on top) */
    for (int i = g->snake.length - 1; i >= 0; i--) {
        draw_snake_segment(&g->snake, i);
    }

    /*status bar*/
    char left[48];
    char right[24];

    if (g->state == STATE_GAME_OVER)      snprintf(left, sizeof(left), "Game over.");
    else if (g->state == STATE_WON)       snprintf(left, sizeof(left), "The garden is full!");
    else if (g->state == STATE_PAUSED)    snprintf(left, sizeof(left), "Paused");
    else if (g->lastAte >= 0)             snprintf(left, sizeof(left), "Ate: %s", flower_info(g->lastAte)->name);
    else                                  snprintf(left, sizeof(left), "Eat the flowers!");

    snprintf(right, sizeof(right), "Length: %d", g->snake.length);
    retro_draw_status(left, right);

    /*popups*/
    if (g->state == STATE_GAME_OVER) {
        retro_message_box("hananinatte", "Game Over!", "Press Enter to retry", true);
    } else if (g->state == STATE_WON) {
        retro_message_box("hananinatte", "You win!", "Press Enter to replay", false);
    } else if (g->state == STATE_PAUSED) {
        retro_message_box("hananinatte", "Paused", "Press P to resume", false);
    }

    retro_draw_taskbar();
}
