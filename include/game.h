#ifndef GAME_H_
#define GAME_H_

#include "settings.h"

Game* g_new( char* name );
void run_game( Game* game );

#endif // GAME_H_