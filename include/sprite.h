#ifndef SPRITE_H_
#define SPRITE_H_

#include "settings.h"

typedef struct Sprite Sprite;

struct Sprite {
    Texture2D* texture;
    Vector2 position;
    Vector2 direction;
    Vector2 size;

    float angle;
    float speed;

    bool active;

    void ( *update )( Sprite*, float );
};

#endif // SPRITE_H_