#ifdef __cplusplus
#include <cstdlib>
#else
#include <stdlib.h>
#endif
#ifdef __APPLE__
#include <SDL/SDL.h>
#else
#include <SDL.h>
#endif
#include "sGraphics.h"
#include "sInput.h"
#include "sSound.h"
#include "game.h"
#include "menu.h"
#include "MersenneTwister.h"
#include <iostream>
#include <string>
#define TotalEnemies 20

using namespace std;
SDL_Graphics gfx(800, 576, 32, SDL_HWSURFACE| SDL_DOUBLEBUF |SDL_FULLSCREEN);

SDL_Input in;
SDL_Sound sfx(22050);
MTRand mtrandl;
bool gameover = false;
SDL_Surface *good = gfx.LoadImageTrans("gfx/tanki28.png", 0, 0,0);
SDL_Surface *bad = gfx.LoadImageTrans("gfx/EnemyTanks.png", 0, 0,0);
SDL_Surface *bricks = gfx.LoadImageAlpha("gfx/bricks.png");
SDL_Surface *img_bullet = gfx.LoadImageAlpha("gfx/bullet.png");
SDL_Surface *sidebar = gfx.LoadImageAlpha("gfx/sidebar.png");

Mix_Chunk *sample = sfx.LoadSample("sfx/laser.wav");

enum choices { SinglePlayer = 1, DoublePlayer, Instructions, Credits, Quit};

int main ( int argc, char** argv )
{
    GameCore game;

    //bool *keystate = in.GetKeyState();

    bool gameend = false;
    do {

    int choice = game.Menu();


    switch(choice) {
        case SinglePlayer: {
            game.Play(1); break;
        }
        case DoublePlayer: {
            game.Play(2); break;
        }

        case Instructions: game.Instructions(); break;

        case Credits: game.Credits(); break;

        case Quit: gameend = true;

        default: break;
    }
    gfx.Wait(500);
    }
    while(!gameend);
    gfx.FreeImage(good);
    gfx.FreeImage(bad);
    gfx.FreeImage(bricks);
    gfx.FreeImage(img_bullet);

    printf("Exited cleanly\n");
    return 0;
}
