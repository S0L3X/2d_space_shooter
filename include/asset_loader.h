#ifndef ASSET_LOADER_H_
#define ASSET_LOADER_H_

#include "settings.h"


typedef struct Textures {
    int size;
    int capacity;
    Texture2D* entries;
} Textures;

void init_textures( Textures* textures, int capacity );
void load_textures( Textures* textures, const char** paths, int count );

#endif // ASSET_LOADER_H_