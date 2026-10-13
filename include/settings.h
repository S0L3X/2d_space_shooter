#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define UNUSED(x) (void)(x)

#define VIRTUAL_SCREEN_WIDTH 1920
#define VIRTUAL_SCREEN_HEIGHT 1080

#define SCALE 80
#define WINDOW_WIDTH 16*SCALE
#define WINDOW_HEIGHT 9*SCALE

#define MAX_SPRITES 10

#define MAX_METEORS 10

#define MAX_LASERS 2
#define LASER_SPEED 600

#define GAME_TITLE "2D Space Shooter"

#define BG_COLOR CLITERAL(Color){ 15, 10, 25, 255 }

typedef struct Game Game;
typedef struct Item Item;
typedef struct RingBuffer RingBuffer;

typedef enum SpriteType {
    PLAYER = 0,
    LASER,
    METEOR,
    STAR,
    NUM_SPRITE_TYPES
} SpriteType;

// static const char* SpriteTypeNames[NUM_SPRITE_TYPES] = {
//     "PLAYER", "LASER", "METEOR", "STAR"
// };

#endif // SETTINGS_H_