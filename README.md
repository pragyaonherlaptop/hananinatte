# hananinatte 𓆙
a 2-d game in c for practice.

# about it:

A retro, Windows 95-style Snake game written in C with [Raylib](https://www.raylib.com/).

## Controls
- Arrow keys / WASD: move
- P: pause
- Enter / Space (or click the smiley): restart
- Esc: quit

## HUD
- Left LCD = score, right LCD = best score
- Smiley changes when you lose or win

## Build & Run
Requires Raylib 4.0 or newer.


```bash
make
./snake
```

## Tweaks (`src/config.h`)
- `SCALE`: window zoom (2 or 3)
- `MOVE_INTERVAL`: game speed
- `FLOWERS_ON_FIELD`: how many flowers appear at once
- `GRID_W` / `GRID_H`: playfield size (adjust the layout constants too)

## Project Structure
| File | Purpose |
|------|---------|
| `src/main.c` | Window, low-res render target, main loop |
| `src/game.c/.h` | Game state, input, update, drawing |
| `src/snake.c/.h` | Snake data and movement |
| `src/flower.c/.h` | Flower types, colors, pixel sprite |
| `src/retro.c/.h` | Windows 95 UI drawing (bevels, title bar, taskbar, dialogs) |
| `src/config.h` | Sizes, speed, layout constants |
