#include "asset_loader.h"

#define MIN_TEXTURES 5

void init_textures( Textures* textures, int capacity ) {
    int minimum_capacity = ( capacity > 0 ) ? capacity : MIN_TEXTURES;
    textures->capacity = minimum_capacity;
    textures->entries = malloc( sizeof( Texture2D ) * textures->capacity );
    textures->size = 0;
}

static void add_texture( Textures* textures, const char* path ) {
    Texture2D texture = LoadTexture( path );
    if ( !texture.id ) {
        printf( "[Error]: Unable to load [%s] texture\n", path );
        return;
    }

    if ( textures->size >= textures->capacity ) {
        textures->capacity *= 2;
        textures->entries = realloc(
            textures->entries,
            textures->capacity * sizeof( *textures->entries )
        );
    }

    textures->entries[textures->size++] = texture;
}

void load_textures( Textures* textures, const char** paths, int count ) {
    puts( "Loading textures..." );
    for ( int i = 0; i < count; i++ )
    {
        add_texture( textures, paths[i] );
    }
}