#ifndef FONT_H
#define FONT_H

#include <SDL/SDL_ttf.h>
#include "Picture.h"

class Font:public Picture
{
private:
 TTF_Font *font;
 SDL_Color textColor;
public:
 Font(int x,int y,char* fontType, int size=25);
 ~Font();
 void setText(const char* txt);
 void setColor(int r,int g, int b);
};

#endif
