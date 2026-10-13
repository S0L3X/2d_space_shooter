#include "game.h"
#include "laser.h"
#include "meteor.h"
#include "ring_buffer.h"
#include "asset_loader.h"


static const char* SpriteURLS[NUM_SPRITE_TYPES] = {
    "assets/images/spaceship.png",
    "assets/images/laser.png",
    "assets/images/meteor.png",
    "assets/images/star.png",
};

struct Game {
    char* name;

    Textures textures;

    RingBuffer laser_rb;
    RingBuffer meteor_rb;

    void ( *run )( Game* );
    void ( *init )( Game* );
    void ( *destroy )( Game* );
};

static void g_input( Game* g ) {
    Vector2 position = { WINDOW_WIDTH / 2, WINDOW_HEIGHT - 50 };
    if ( IsKeyPressed( KEY_SPACE ) ) {
        fire_laser( &g->laser_rb, position );
    }
}

static void g_update_ring_buffers( Game* g, float dt ) {
    g->laser_rb.update( &g->laser_rb, dt );
    g->meteor_rb.update( &g->meteor_rb, dt );
}

static void g_init( Game* g ) {
    SetRandomSeed( time( NULL ) );
    InitWindow( WINDOW_WIDTH, WINDOW_HEIGHT, g->name );
    SetTargetFPS( 60 );
    load_textures( &g->textures, SpriteURLS, NUM_SPRITE_TYPES );

    rb_init( &g->laser_rb, LASER );
    rb_init( &g->meteor_rb, METEOR );

    init_meteors( &g->meteor_rb, &g->textures.entries[METEOR] );
    printf( "%s is initialized!\n", g->name );
}

static void g_dtor( Game* g ) {
    free( g->textures.entries );
    free( g->laser_rb.items );
    free( g->meteor_rb.items );
    free( g );

    CloseWindow();
}

static void g_update( Game* g, float dt ) {
    g_input( g );
    g_update_ring_buffers( g, dt );
}

static void g_render( Game* g ) {
    BeginDrawing();
    ClearBackground( BG_COLOR );

    draw_meteor( &g->meteor_rb );
    draw_laser( &g->laser_rb );
    
    
    DrawText( g->name, 20, 20, 24, GOLD );
    EndDrawing();
}

static void g_run( Game* g ) {
    g->init( g );

    while ( !WindowShouldClose() ) {
        float dt = GetFrameTime();
        g_update( g, dt );
        g_render( g );
    }

    g->destroy( g );
}

static void g_ctor( Game* g ) {
    init_textures( &g->textures, NUM_SPRITE_TYPES );

    g->run = g_run;
    g->init = g_init;
    g->destroy = g_dtor;
}

Game* g_new( char* name ) {
    Game* g = malloc( sizeof( Game ) );
    if ( !g ) exit( EXIT_FAILURE );

    g->name = name;

    g_ctor( g );
    return g;
}

void run_game( Game* g ) {
    g->run( g );
}