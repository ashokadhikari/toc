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

SDL_Graphics gfx(800, 600);
SDL_Input in;

SDL_Surface* image;
int main ( int argc, char** argv )
{
    bool* keystate = in.GetKeyState();
    MouseInfo *minfo = in.GetMouseState();
    bool done = false;
    while(!done) {
        in.ProcessEvents();
        if(in.QuitRequest()) done = true;
        if(minfo -> button[MU_LEFT]) done = true;

        gfx.ClearScreen();
        gfx.PutImage(image,200, 200);
        gfx.FlipDrawing();
    }
    printf("Exited cleanly\n");
    return 0;
}
