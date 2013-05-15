#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED
#include <SDL.h>

extern bool gameover;
extern bool *keystate;
extern SDL_Graphics gfx;
extern SDL_Input in;
extern SDL_Sound sfx;
extern MTRand mtrandl;

extern SDL_Surface *good;
extern SDL_Surface *bad;
extern SDL_Surface *bricks;
extern SDL_Surface *sidebar;
extern SDL_Surface *img_bullet;
extern Mix_Chunk *sample;
extern const int MaxEnemy;
extern bool dble;
extern int NumPlayers;
extern bool Level_Complete;
extern int map_id;

#endif // GLOBALS_H_INCLUDED
