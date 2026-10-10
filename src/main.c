#include "game.h"

int main( void )
{
    Game* game = g_new( GAME_TITLE );
    run_game( game );

    return 0;
}
