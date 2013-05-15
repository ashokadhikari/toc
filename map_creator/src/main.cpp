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
#include <fstream>
#include <iostream>
#include "sGraphics.h"
#include "sInput.h"
#include <string>
#define BW 32
#define BH 32
#define location "J:/Documents and Settings/Tomiferous/Desktop/out/Tank/maps/"
#define MAP_NO 1


using namespace std;

SDL_Graphics gfx(800, 576, 32, SDL_DOUBLEBUF|SDL_HWSURFACE);
SDL_Input in;

SDL_Surface* bricks = gfx.LoadImageAlpha("gfx/bricks.png");

int field[18][25] = {0};
int fill_field(int , int, int);
void writetofile(int);

enum blocktypes {GRASS = 1 , TRANSPARENT, EAGLE, UNBREAKABLE, BREAKABLE};
enum cliptype {CLIPBREAK = 0, CLIPGRASS, CLIPTRANS, CLIPEAGLE, CLIPUNBREAK};
int main ( int argc, char** argv )
{


    bool* keystate = in.GetKeyState();
    MouseInfo *minfo = in.GetMouseState();
    bool done = false;
    bool write = false;

    SDL_Rect clip;
    clip.y = 0; clip.w = BW; clip.h = BH;
    int type = 1;
    while(!done) {

            field[0][3] = BREAKABLE;
            field[0][5] = GRASS;
            field[0][7] = TRANSPARENT;
            field[0][9] = EAGLE;
            field[0][11] = UNBREAKABLE;

        in.ProcessEvents();
        if(in.QuitRequest()) done = true;
        if(keystate[SDLK_ESCAPE]) {done = true;}
        if(keystate[SDLK_RETURN]) {write = true;}
        //if(keystate[SDLK_SPACE]) {done = true;}//while(keystate[SDLK_SPACE]) {flag = true; done = true;}
        if(minfo -> button[MU_LEFT]) {
             int x = minfo -> x / BW;
             int y = minfo -> y / BH;
             if(x == 3 && y == 0) type = BREAKABLE;
             if(x == 5 && y == 0) type = GRASS;
             if(x == 7 && y == 0) type = TRANSPARENT;
             if(x == 9 && y == 0) type = EAGLE;
             if(x == 11 && y == 0) type = UNBREAKABLE;
             if(x > 11 && y == 0) type = 0;
             fill_field(x, y, type);
        }

        //if(!minfo -> button[MU_LEFT]) fill_field(minfo -> x, minfo -> y, type);

        gfx.ClearScreen();

        //SDL_FillRect(gfx.screen, 0, SDL_MapRGB(gfx.screen -> format, 255,155 ,0));
     /*  for(int j = 0; j < gfx.screen -> h / BH; j++) {
            for(int i = 0; i < gfx.screen -> w / BW; i++) {
            mapfield[j][i] = gamefield[j * 2][i * 2];
            }
            }*/

        for(int j = 0; j < gfx.screen -> h / BH; j++) {
            for(int i = 3; i < gfx.screen -> w / BW - 3; i++) {
                if(field[j][i] == BREAKABLE) {clip.x = CLIPBREAK * BW; gfx.PutImage(bricks, gfx.screen , &clip, i * BW, j * BH);}
                if(field[j][i] == GRASS) {clip.x = CLIPGRASS * BW; gfx.PutImage(bricks, gfx.screen , &clip, i * BW, j * BH);}
                if(field[j][i] == TRANSPARENT) {clip.x = CLIPTRANS * BW; gfx.PutImage(bricks, gfx.screen , &clip, i * BW, j * BH);}
                if (field[j][i] == EAGLE) {clip.x = CLIPEAGLE * BW; gfx.PutImage(bricks, gfx.screen , &clip, i * BW, j * BH);}
                if (field[j][i] == UNBREAKABLE) {clip.x = CLIPUNBREAK * BW; gfx.PutImage(bricks, gfx.screen , &clip, i * BW, j * BH);}

            }
        }
        gfx.FlipDrawing();
        }

    if(write) writetofile(MAP_NO);

    printf("Exited cleanly\n");
    return 0;
}

int fill_field(int x, int y, int type) {
    field[y][x] = type;
    if( y == 0 ) field[y][x] = 0;
    if(x <= 2) field[y][x] = 0;
    if(x >= 22) field[y][x] = 0;
    return 0;
}

void writetofile(int filenum) {
    int readymade[18][25] = {0};
    char str[10];
    sprintf(str, "%d", filenum);
    string s = str;
    string filename;
    filename = "map" + s;
    filename += ".map";
    filename = location + filename;
    ofstream outfile(filename.c_str());

    for(int j = 0; j < 18; j++) {
        for(int i = 0; i < 25 ; i++) {
            if(j == 0) {readymade[j][i] = 0;}
            else if(j <= 14) readymade[j][i] = field[j][i];

            }
        }
        for(int j = 16; j < 18; j++)
            for(int i = 10; i < 14; i++) {
                if(i == 10 || i == 14) readymade[j][i] = 0;
                if(i == 11 || i == 13 || i == 12) readymade[j][i] = BREAKABLE;
                if(i == 12 && j == 17) readymade[j][i] = EAGLE;
    }
    for(int j = 0; j < 18; j++) {
        cout << endl;
        for(int i = 0; i < 25; i++) {
        outfile << readymade[j][i];
        outfile <<' ' ;
        cout << readymade[j][i];
        }
        }

}
