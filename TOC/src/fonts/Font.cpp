#include "Font.h"

Font::Font(int x, int y,char* fontType, int size)
{
TTF_Init();
setx(x);
sety(y);
font=TTF_OpenFont(fontType,size);
}

Font::~Font()
{
TTF_CloseFont( font ); 
TTF_Quit(); //QuitSDL_ttf 
}

void Font::setText(const char* txt)
{
TTF_SetFontStyle(font, TTF_STYLE_BOLD);//|TTF_STYLE_ITALIC);
surface=TTF_RenderText_Solid(font,txt,textColor);
}

void Font::setColor(int r,int g, int b)
{
textColor.r=r;
textColor.g=g;
textColor.b=b;
}
