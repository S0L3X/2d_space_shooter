#include "game.h"

int main( void )
{
    SetTraceLogLevel(LOG_WARNING);
    
    Game* game = g_new( GAME_TITLE );
    run_game( game );

    return 0;
}
