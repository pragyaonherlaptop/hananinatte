#ifndef CONFIG_H
#define CONFIG_H

/* Playfield*/
#define CELL_SIZE        10
#define GRID_W           24
#define GRID_H           16
#define MAX_SNAKE        (GRID_W * GRID_H)
#define FLOWERS_ON_FIELD 3
#define WIN_LENGTH       (MAX_SNAKE - FLOWERS_ON_FIELD)
#define MOVE_INTERVAL    0.14f   /* seconds per step; lower = faster */

/*Low-res "virtual" screen, scaled up for the pixel look*/
#define VIRT_W    288
#define VIRT_H    272
#define SCALE     2              /* use 3 on big monitors */
#define SCREEN_W  (VIRT_W * SCALE)
#define SCREEN_H  (VIRT_H * SCALE)

/*Window layout (in virtual pixels) it'll look nice lol*/
#define WIN_X     8
#define WIN_Y     6
#define WIN_W     272
#define WIN_H     240

#define FIELD_X   24
#define FIELD_Y   60
#define FIELD_W   (GRID_W * CELL_SIZE)
#define FIELD_H   (GRID_H * CELL_SIZE)

/*HUD (score panel)*/
#define HUD_Y     33
#define HUD_H     22
#define LCD_Y     36
#define LCD_W     30
#define LCD_H     16
#define LCD_L_X   14
#define LCD_R_X   245
#define FACE_X    136
#define FACE_Y    36
#define FACE_SIZE 16

/*Status bar*/
#define STATUS_Y  226
#define STATUS_H  14

#endif
