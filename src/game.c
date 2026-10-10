#include "game.h"
#include "laser.h"
#include "meteor.h"
#include "ring_buffer.h"

struct Game {
    char* name;
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

static void g_update_ring_buffers( Game* g ) {
    g->laser_rb.update( &g->laser_rb );
    g->meteor_rb.update( &g->meteor_rb );
}

static void g_init( Game* g ) {
    SetRandomSeed( time( NULL ) );
    InitWindow( WINDOW_WIDTH, WINDOW_HEIGHT, g->name );
    SetTargetFPS( 60 );

    rb_init( &g->laser_rb, LASER );
    rb_init( &g->meteor_rb, METEOR );

    init_meteors( &g->meteor_rb );
    printf( "%s is initialized!\n", g->name );
}

static void g_dtor( Game* g ) {
    free( g->laser_rb.items );
    free( g->meteor_rb.items );
    free( g );

    CloseWindow();
}

static void g_update( Game* g ) {
    g_input( g );
    g_update_ring_buffers( g );
}

static void g_render( Game* g ) {
    BeginDrawing();
    ClearBackground( BG_COLOR );
    
    DrawText( g->name, 20, 20, 24, GOLD );
    draw_meteor( &g->meteor_rb );
    draw_laser( &g->laser_rb );
    
    EndDrawing();
}

static void g_run( Game* g ) {
    g->init( g );

    while ( !WindowShouldClose() ) {
        g_update( g );
        g_render( g );
    }

    g->destroy( g );
}

static void g_ctor( Game* g ) {
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