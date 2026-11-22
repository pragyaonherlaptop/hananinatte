#include <time.h>
#include "raylib.h"
#include "config.h"
#include "game.h"

int main(void)
{
    InitWindow(SCREEN_W, SCREEN_H, "Snake 95");
    SetTargetFPS(60);
    SetRandomSeed((unsigned int)time(NULL));

    /* Draw everything at low resolution, then scale up with no smoothing. */
    RenderTexture2D target = LoadRenderTexture(VIRT_W, VIRT_H);
    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);
    SetTextureFilter(GetFontDefault().texture, TEXTURE_FILTER_POINT);

    Game game;
    game_init(&game);

    while (!WindowShouldClose()) {
        game_handle_input(&game);
        game_update(&game, GetFrameTime());

        BeginTextureMode(target);
        game_draw(&game);
        EndTextureMode();

        BeginDrawing();
        ClearBackground(BLACK);
        DrawTexturePro(target.texture,
                       (Rectangle){ 0, 0, (float)VIRT_W, -(float)VIRT_H },
                       (Rectangle){ 0, 0, (float)SCREEN_W, (float)SCREEN_H },
                       (Vector2){ 0, 0 }, 0.0f, WHITE);
        EndDrawing();
    }

    UnloadRenderTexture(target);
    CloseWindow();
    return 0;
}
