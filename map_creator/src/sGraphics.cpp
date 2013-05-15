#include "sGraphics.h"

//initialise graphics
SDL_Graphics::SDL_Graphics(int w, int h, int bpp, Uint32 flags) {
    SDL_InitSubSystem(SDL_INIT_VIDEO);
    TTF_Init();

    screen = SDL_SetVideoMode(w, h, bpp, flags);
    bgColor = SDL_MapRGB(screen -> format, 0,0,0);
}

SDL_Graphics::~SDL_Graphics() {
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
    TTF_Quit();
}

void SDL_Graphics::SetBgColor(int r, int g, int b) {
    SDL_MapRGB(screen -> format, r,g,b);
}

SDL_Surface* SDL_Graphics::LoadImage(const char *filename) {
    SDL_Surface *loadedImage = NULL;
    SDL_Surface *optimised = NULL;

    if((loadedImage = IMG_Load(filename)) == NULL) printf("%d", IMG_GetError());

    if(loadedImage != NULL) {
        optimised = SDL_DisplayFormat(loadedImage);
        SDL_FreeSurface(loadedImage);

    }
    return optimised;
}

SDL_Surface* SDL_Graphics::LoadImageTrans(const char *filename, int transR, int transG, int transB) {
    SDL_Surface *loadedImage = NULL;
    SDL_Surface *optimised = NULL;

    if((loadedImage = IMG_Load(filename)) == NULL) printf("%d", IMG_GetError());

    if(loadedImage != NULL) {
        Uint32 colorkey;
        colorkey = SDL_MapRGB(screen -> format, transR, transG, transB);
        SDL_SetColorKey(loadedImage, SDL_SRCCOLORKEY, colorkey);
        optimised = SDL_DisplayFormat(loadedImage);
        SDL_FreeSurface(loadedImage);
    }
    return optimised;
}

SDL_Surface* SDL_Graphics::LoadImageAlpha(const char *filename) {
    SDL_Surface *loadedImage = NULL;
    SDL_Surface *optimised = NULL;

    if((loadedImage = IMG_Load(filename)) == NULL) printf("%d", IMG_GetError());

    if(loadedImage != NULL) {
        optimised = SDL_DisplayFormatAlpha(loadedImage);
        SDL_FreeSurface(loadedImage);
    }
    return optimised;
}

void SDL_Graphics::PutImage(SDL_Surface *src, SDL_Surface *dst,SDL_Rect *clip, int x, int y) {
    static SDL_Rect dstrect;
    dstrect.x = x;
    dstrect.y = y;

    SDL_BlitSurface(src, clip, dst, &dstrect);
}

void SDL_Graphics::PutImage(SDL_Surface *src, int x, int y) {
    static SDL_Rect dstrect;
    dstrect.x = x;
    dstrect.y = y;

    SDL_BlitSurface(src, NULL, screen, &dstrect);
}

void SDL_Graphics::ClearScreen() {
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen -> format, 0,0,0));
}

void SDL_Graphics::FlipDrawing() {
    SDL_Flip(screen);
}
