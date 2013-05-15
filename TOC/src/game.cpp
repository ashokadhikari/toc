#include "game.h"
#include "sGraphics.h"
#include "sInput.h"
#include "sSound.h"
#include "globals.h"
#include <conio.h>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
enum blocktypes {GRASS = 1, TRANSPARENT, EAGLE, UNBREAKABLE, BREAKABLE};
enum directions {LEFT = -1, UP = -1, RIGHT = 1, DOWN = 1, NOT = 0};
enum cliptype {CLIPGRASS = 0, CLIPTRANS, CLIPEAGLE, CLIPUNBREAK, CLIPBREAK, CLIPBREAK_1, CLIPBREAK_2 };
enum cliptype_tank {C_DOWN = 0, C_UP, C_LEFT, C_RIGHT};

Tank::Tank(int num) {
    prev_x = x = 270 + (num - 1) * 190;
    prev_y = y = 546;
    dx = .3;
    dy = .3;
    xdirection = NOT;
    ydirection = DOWN;
    motion = true;
    size_w = TW ;size_h = TH;
    cout << x <<" "<< y <<endl;
    active = true;


}

Tank::Tank() {
    prev_x = x = 600; prev_y =  y = 0;
    dx = .2; dy = .2;
    xdirection = NOT;
    ydirection = DOWN;
    size_w = TW ;size_h = TH;
    active = true;
}

int EnemyTank::TankPos = 0;
int EnemyTank::resetPriority = 0;
int EnemyTank::priority[];

Tank::Tank(float a, float b) {
    prev_x = x = 20;
    prev_y = y = 77;
    dx = .2; dy = .2;

    xdirection = NOT;
    ydirection = DOWN;
    active = true;

}

Tank::Tank(float rate) {
    dx += rate;
    dy += rate;
}

bool Tank::IsActive() {
    return active;
}

int Tank::CheckPosition(Blocks bk) {
    int i[4] = {0}, j[4] = {0}, t = 0, dontmove = false, extreme[4] = {0};
    for(int h = 0; h < 2; h++ ) {
        for(int g = 0; g < 2; g++ ) {
            i[t] = (((int)x + 2 + g * (TW - 2)) / BW);
            j[t] = (((int)y + 2 + h * (TH - 2)) / BH);

            for(int hem = GRASS; hem <= BREAKABLE; hem++)
                if(bk.field[j[t]][i[t]] == hem) {extreme[t] = hem;}//needs change
            t++;

    }
    }

    for(int i = 0; i < 4; i++) if(extreme[i] == BREAKABLE || extreme[i] == TRANSPARENT || extreme[i] == EAGLE || extreme[i] == UNBREAKABLE) dontmove = true;
    if(x > (gfx.screen -> w - 3 * BW) - TW || x < 3 * BW || y < 0 || y > (gfx.screen -> h - TH) ) dontmove = true;
    if(dontmove) {
        x = prev_x;
        y = prev_y;
        backoff = true;//return the enemy tank in opposite direction,, to be changed
        return 1;
    }
    else backoff = false;
    return 0;

}

void GoodTank::UpdateCord() {
        bool *keystate = in.GetKeyState();
        clip.y = 1;
        prev_x = x;
        prev_y = y;

        in.ProcessEvents();

        if(TankNo == 1) {
        static bool priority[4];
        static bool sync[4];
        if(keystate[SDLK_RIGHT] & priority[0]) {
            clip.x =  TW * C_RIGHT;
            x += dx;

            priority[0] = true;
            sync[0] = true;
            for(int i  = 0; i <= 3; i++)  if (i != 0) {priority[i] = false; sync[i] = false;}
            xdirection = RIGHT;
            ydirection = NOT;
        }


        else if(keystate[SDLK_LEFT] & priority[1]) {
            clip.x = TW * C_LEFT;
            x -= dx;

            priority[1] = true;
            sync[1] = true;
            for(int i  = 0; i <= 3; i++)  if (i != 1) {priority[i] = false; sync[i] = false;}
            xdirection = LEFT;
            ydirection = NOT;
            }


        else if(keystate[SDLK_UP] & priority[2]) {
            clip.x = TW * C_UP;
            y -= dy;

            priority[2] = true;
            sync[2] = true;
            for(int i = 0; i <= 3; i++)  if (i != 2) {priority[i] = false; sync[i] = false;}
            xdirection = NOT;
            ydirection = UP;
        }


        else if(keystate[SDLK_DOWN] & priority[3]) {
            clip.x = C_DOWN;
            y += dy;

            priority[3] = true;
            sync[3] = true;
            for(int i = 0; i <= 3; i++)  if (i != 3) {priority[i] = false; sync[i] = false;}
            xdirection = NOT;
            ydirection = DOWN;
        }

        else {
            if(sync[0] == true) {if(((int)((x - 2) * 10) % 40) != 0) x+=dx; else {sync[0] = false; }}
            if(sync[1] == true) {if(((int)((x + 2) * 10) % 40) != 0) x-=dx; else {sync[1] = false; }}
            if(sync[2] == true) {if(((int)((y + 2) * 10) % 40) != 0) y-=dy; else {sync[2] = false; }}
            if(sync[3] == true) {if(((int)((y - 2) * 10) % 40) != 0) y+=dy; else {sync[3] = false; }}
            for(int i = 0; i <= 3; i++) priority[i] = true;

        }

        }

        if(TankNo == 2) {
        static bool Tpriority[4];
        static bool Tsync[4];
        if(keystate[SDLK_d] & Tpriority[0]) {
            clip.x =  TW * C_RIGHT;
            x += dx;

            Tsync[0] = true;
            Tpriority[0] = true;
            for(int i = 0; i <= 3; i++)  if (i != 0) {Tpriority[i] = false; Tsync[i] = false;}
            xdirection = RIGHT;
            ydirection = NOT;
        }


        else if(keystate[SDLK_a] & Tpriority[1]) {
            clip.x = TW * C_LEFT;
            x -= dx;

            Tsync[1] = true;
            Tpriority[1] = true;
            for(int i  = 0; i <= 3; i++)  if (i != 1) {Tpriority[i] = false; Tsync[i] = false;}
            xdirection = LEFT;
            ydirection = NOT;
            }


        else if(keystate[SDLK_w] & Tpriority[2]) {
            clip.x = TW * C_UP;
            y -= dy;

            Tsync[2] = true;
            Tpriority[2] = true;
            for(int i = 0; i <= 3; i++)  if (i != 2) {Tpriority[i] = false; Tsync[i] = false;}
            xdirection = NOT;
            ydirection = UP;
        }


        else if(keystate[SDLK_s] & Tpriority[3]) {
            clip.x = TW * C_DOWN;
            y += dy;

            Tsync[3] = true;
            Tpriority[3] = true;
            for(int i = 0; i <= 3; i++)  if (i != 3) {Tpriority[i] = false; Tsync[i] = false;}
            xdirection = NOT;
            ydirection = DOWN;
        }

        else {
            if(Tsync[0] == true) {if(((int)((x - 2) * 10) % 40) != 0) x+=dx; else {Tsync[0] = false; }}
            if(Tsync[1] == true) {if(((int)((x + 2) * 10) % 40) != 0) x-=dx; else {Tsync[1] = false; }}
            if(Tsync[2] == true) {if(((int)((y + 2) * 10) % 40) != 0) y-=dy; else {Tsync[2] = false; }}
            if(Tsync[3] == true) {if(((int)((y - 2)* 10) % 40) != 0) y+=dy; else {Tsync[3] = false; }}
            for(int i = 0; i <= 3; i++) Tpriority[i] = true;

        }
        }
}

int Tank::CheckCollide(GoodTank gt) {
    float fx = gt.x, fy = gt.y;
    float hx = x, hy = y;
    bool collision = false;

    if(hy + TH < fy or hx > fx + TW or hy > fy + TH or hx + TH < fx)
        collision = false;
    else collision = true;

    if(collision) {
        x = prev_x;
        y = prev_y;
        return 1;
    }
    return 0;
}

int Tank::CheckCollide(EnemyTank gt) {
    float fx = gt.x, fy = gt.y;
    float hx = x, hy = y;
    bool collision;

    if(hy + TH < fy or hx > fx + TW or hy > fy + TH or hx + TH < fx)
        collision = false;
    else collision = true;

    if(collision) {
        x = prev_x;
        y = prev_y;
        return 1;
    }
    return 0;
}

Blocks::Blocks() {
    clip.x = 0; clip.y = 0; clip.w = BW; clip.h = BH;
    size_w = BW ;size_h = BH;
    for(int j = 0; j < gfx.screen -> h / BH; j++)
        for(int i = 0; i < gfx.screen -> w / BW; i++) {
            field[j][i] = 0;
            life[j][i] = 1;
        }
}

void Blocks::LoadMap(int map_no) {
    int type;
    char str[10];
    string filename;
    sprintf(str, "%d", map_no);
    string s = str;
    filename = "maps/map" + s;
    filename += ".map" ;
    ifstream infile(filename.c_str());

    for(int j = 0; j < gfx.screen -> h / BH; j++) {
        for(int i = 0; i < gfx.screen -> w / BW; i++) {
            infile >> type;
            field[j][i] = type;
    }
    }
}

void Blocks::RenderMap(void) {
    for(int j = 0; j < gfx.screen -> h / BH; j++)
        for(int i = 0; i < gfx.screen -> w / BW; i++) {
            if(!field[j][i]) continue;
            else for(int hem = GRASS; hem <=BREAKABLE; hem++)
                if(field[j][i] == hem) {
                clip.x = (hem - 1) * BW;
                gfx.PutImage(bricks, gfx.screen , &clip, i * BW, j * BH);
                }
        }
}

Bullet::Bullet(int Btime) {
    prev_x = x = 0; prev_y = y = 0;
    size_w = img_bullet -> w ;size_h = img_bullet -> h;
    dx = 1; dy = 1;
    endPath = true;
    firsttime = false;
    onPath = false;
    Collison = false;
    Wait = false;
    limit = RecoilTime = Btime;
    level = 1;
    renderon = 0;
    active1 = false;
    active2 = true;
}

void Bullet::ResetAttrib() {
    endPath = true;
    firsttime = false;
    onPath = false;
    Collison = false;
    Wait = false;
    level = 1;
    renderon = 0;
    active1 = false;
    active2 = true;
}
void Bullet::UpdateBullet(Blocks *bk) {
    prev_x = x; prev_y = y;

    x+=(xdir * dx);
    y+=(ydir * dy);

    int i = (int)x/BW, j = (int)y/BH;
    if(bk -> field[j][i] == EAGLE) {gameover = true; printf("Gameover"); }
    if(bk -> field[j][i] == UNBREAKABLE) {endPath = true; onPath = false;renderon = 1;if(active1) active2 = false;}
    else if(bk -> field[j][i] == BREAKABLE) {--bk -> life[j][i]; if(bk -> life[j][i] == 0) bk -> field[j][i] = 0; endPath = true; onPath = false; renderon = 1; if(active1) active2 = false;}
    else if(x <= 3 * BW || y <= 0 || x >= ((gfx.screen -> w) - 3 * BW - (img_bullet -> w)) || y >= ((gfx.screen ->h) - (img_bullet -> h))) { endPath = true; onPath = false;renderon = 1;if(active1) active2 = false;}
    else {onPath = true; endPath = false;}
}

void Bullet::BulletSound() {
    if(firsttime) {sfx.PlaySample(-1, sample, 0); firsttime = false;}
}


int Bullet::CheckCollide(GoodTank gt) {////t2 hits t1//
    float fx = gt.x, fy = gt.y;
    float hx = x, hy = y;
    bool collision;

    if(hy + size_h < fy or hx > fx + TW or hy > fy + TH or hx + size_w < fx)
        collision = false;
    else collision = true;

    if(collision) {
        endPath = true; onPath = false; renderon = 1;
        return 1;
    }
    return 0;
}

int Bullet::CheckCollide(EnemyTank gt, bool dummy) {////t2 hits t1//
    float fx = gt.x, fy = gt.y;
    float hx = x, hy = y;
    bool collision;

    if(hy + size_h < fy or hx > fx + TW or hy > fy + TH or hx + size_w < fx)
        collision = false;
    else collision = true;

    if(collision) {
        if(dummy) {endPath = true; onPath = false; renderon = 1;}
        return 1;
    }
    return 0;
}

void Bullet::BlackTime() {
    if(Wait) RecoilTime-=1;
    if(RecoilTime == 0) {RecoilTime = limit ; Wait = false;}

}
void Bullet::SetTrigger(GoodTank tk) {
    if(endPath & !Wait) {
        x = (tk.x + TW/2 - 1); y = (tk.y + TH/2 - 2);
        onPath = true;
        firsttime = true;
        Wait = true;
        xdir = tk.GetXDirection();
        ydir = tk.GetYDirection();
        }
}

void Bullet::SetTrigger(EnemyTank et) {
    if(endPath & !Wait) {
        x = (et.x + TW/2 - 1); y = (et.y + TH/2 - 2);
        onPath = true;
        firsttime = true;
        Wait = true;
        xdir = et.GetXDirection();
        ydir = et.GetYDirection();
        }
}

int Bullet::GetOnPath() {
    if(onPath) return 1;
    else return 0;
}

int Bullet::GetEndPath() {
    if(endPath) return 1;
    else return 0;
}

void Frame::SelectiveRender(Blocks bk, GoodTank tk) {
     int i[4] = {0}, j[4] = {0}, t = 0;

    int x = (int)tk.prev_x - 2;
    int y = (int)tk.prev_y - 2;
    for(int h = 0; h < 2; h++ ) {
        for(int g = 0; g < 2; g++ ) {
            i[t] = ((x  + g * (tk.size_w + 2)) / BW);
            j[t] = ((y + h * (tk.size_h + 2)) / BH);
            if(!bk.field[j[t]][i[t]]) gfx.ClearScreen(i[t] * BW, j[t] * BH, BW, BH);
            if(bk.field[j[t]][i[t]] == BREAKABLE) {
                gfx.ClearScreen(i[t] * BW, j[t] * BH, BW, BH);
                if(bk.life[j[t]][i[t]] == 1) clip.x = CLIPBREAK * BW;
                //else if(bk.life[j[t]][i[t]] == 2) clip.x = CLIPBREAK_1* BW;
                //else if(bk.life[j[t]][i[t]] == 1) clip.x = CLIPBREAK_2 * BW;
                gfx.PutImage(bricks, gfx.screen , &clip, i[t] * BW, j[t] * BH);
                }
            if(bk.field[j[t]][i[t]] == TRANSPARENT) {gfx.ClearScreen(i[t] * BW, j[t] * BH, BW, BH); clip.x = CLIPTRANS * BW; gfx.PutImage(bricks, gfx.screen , &clip, i[t] * BW, j[t] * BH);}
            if(bk.field[j[t]][i[t]] == GRASS) {gfx.ClearScreen(i[t] * BW, j[t] * BH, BW, BH); clip.x = CLIPGRASS * BW; gfx.PutImage(bricks, gfx.screen , &clip, i[t] * BW, j[t] * BH);}
            if(bk.field[j[t]][i[t]] == EAGLE) {gfx.ClearScreen(i[t] * BW, j[t] * BH, BW, BH); clip.x = CLIPEAGLE * BW; gfx.PutImage(bricks, gfx.screen , &clip, i[t] * BW, j[t] * BH);}
            if(bk.field[j[t]][i[t]] == UNBREAKABLE) {gfx.ClearScreen(i[t] * BW, j[t] * BH, BW, BH); clip.x = CLIPUNBREAK * BW; gfx.PutImage(bricks, gfx.screen , &clip, i[t] * BW, j[t] * BH);}
            t++;
    }
    }
}

void Frame::SelectiveRender(Blocks bk, EnemyTank tk) {
     int i[4] = {0}, j[4] = {0}, t = 0;
    int x = (int)tk.prev_x;
    int y = (int)tk.prev_y;
    for(int h = 0; h < 2; h++ ) {
        for(int g = 0; g < 2; g++ ) {
            i[t] = ( ( x + g * (tk.size_w) ) / BW);
            j[t] = ( ( y + h * (tk.size_h) ) / BH);
            if(!bk.field[j[t]][i[t]]) gfx.ClearScreen(i[t] * BW, j[t] * BH, BW, BH);
            if(bk.field[j[t]][i[t]] == BREAKABLE) {
                gfx.ClearScreen(i[t] * BW, j[t] * BH, BW, BH);
                if(bk.life[j[t]][i[t]] == 1) clip.x = CLIPBREAK * BW;
                //if(bk.life[j[t]][i[t]] == 2) clip.x = CLIPBREAK_1* BW;
                //if(bk.life[j[t]][i[t]] == 1) clip.x = CLIPBREAK_2 * BW;
                gfx.PutImage(bricks, gfx.screen , &clip, i[t] * BW, j[t] * BH);
                }
            if(bk.field[j[t]][i[t]] == TRANSPARENT) {gfx.ClearScreen(i[t] * BW, j[t] * BH, BW, BH); clip.x = CLIPTRANS * BW; gfx.PutImage(bricks, gfx.screen , &clip, i[t] * BW, j[t] * BH);}
            if(bk.field[j[t]][i[t]] == GRASS) {gfx.ClearScreen(i[t] * BW, j[t] * BH, BW, BH); clip.x = CLIPGRASS * BW; gfx.PutImage(bricks, gfx.screen , &clip, i[t] * BW, j[t] * BH);}
            if(bk.field[j[t]][i[t]] == EAGLE) {gfx.ClearScreen(i[t] * BW, j[t] * BH, BW, BH); clip.x = CLIPEAGLE * BW; gfx.PutImage(bricks, gfx.screen , &clip, i[t] * BW, j[t] * BH);}
            if(bk.field[j[t]][i[t]] == UNBREAKABLE) {gfx.ClearScreen(i[t] * BW, j[t] * BH, BW, BH); clip.x = CLIPUNBREAK * BW; gfx.PutImage(bricks, gfx.screen , &clip, i[t] * BW, j[t] * BH);}
            t++;
    }
    }
}

void Frame::SelectiveRender(Blocks bk, Bullet bt) {
     int i[4] = {0}, j[4] = {0}, t = 0;

    int x = (int)bt.prev_x - 2;
    int y = (int)bt.prev_y - 2;
    for(int h = 0; h < 2; h++ ) {
        for(int g = 0; g < 2; g++ ) {
            i[t] = ((x  + g * (bt.size_w + 2)) / BW);
            j[t] = ((y + h * (bt.size_h + 2)) / BH);
            if(!bk.field[j[t]][i[t]]) gfx.ClearScreen(i[t] * BW, j[t] * BH, BW, BH);
            if(bk.field[j[t]][i[t]] == BREAKABLE) {
                gfx.ClearScreen(i[t] * BW, j[t] * BH, BW, BH);
                //if(bk.life[j[t]][i[t]] == 3) clip.x = CLIPBREAK * BW;
                //else if(bk.life[j[t]][i[t]] == 2) clip.x = CLIPBREAK_1* BW;
                if(bk.life[j[t]][i[t]] == 1) clip.x = CLIPBREAK * BW;
                gfx.PutImage(bricks, gfx.screen , &clip, i[t] * BW, j[t] * BH);
                }
            if(bk.field[j[t]][i[t]] == TRANSPARENT) {gfx.ClearScreen(i[t] * BW, j[t] * BH, BW, BH); clip.x = CLIPTRANS * BW; gfx.PutImage(bricks, gfx.screen , &clip, i[t] * BW, j[t] * BH);}
            if(bk.field[j[t]][i[t]] == GRASS) {gfx.ClearScreen(i[t] * BW, j[t] * BH, BW, BH); clip.x = CLIPGRASS * BW; gfx.PutImage(bricks, gfx.screen , &clip, i[t] * BW, j[t] * BH);}
            if(bk.field[j[t]][i[t]] == EAGLE) {gfx.ClearScreen(i[t] * BW, j[t] * BH, BW, BH); clip.x = CLIPEAGLE * BW; gfx.PutImage(bricks, gfx.screen , &clip, i[t] * BW, j[t] * BH);}
            if(bk.field[j[t]][i[t]] == UNBREAKABLE) {gfx.ClearScreen(i[t] * BW, j[t] * BH, BW, BH); clip.x = CLIPUNBREAK * BW; gfx.PutImage(bricks, gfx.screen , &clip, i[t] * BW, j[t] * BH);}
            t++;
    }
    }
}


void Frame::Blit(Bullet bt) {
    gfx.PutImage(img_bullet, (int)bt.x, (int)bt.y);
}


void Frame::Blit(GoodTank tk) {
    gfx.PutImage(good, gfx.screen, &tk.clip, (int)tk.x,(int)tk.y);
}

void Frame::Blit(EnemyTank tk) {
    gfx.PutImage(bad, gfx.screen, &tk.clip, (int)tk.x,(int)tk.y);
}

void Frame::ShowLife(int life1, int life2) {
    char str[10];
    sprintf(str, "%d", life1);
    gfx.SetTextColor(32, 180, 140);
    gfx.ShowText("Player 1", 10, 134);
    gfx.ShowText("Life:", 10, 164);
    gfx.ClearScreen(10, 184, 16, 16);
    gfx.ShowText(str, 10, 184);
    if(dble) {
        sprintf(str, "%d", life2);
        gfx.ShowText("Player 2", 10, 334);
        gfx.ShowText("Life:", 10, 364);
        gfx.ClearScreen(10, 384, 16, 16);
        gfx.ShowText(str, 10, 384);
    }

    sprintf(str, "%d", EnemyTank::Remaining);
    gfx.ShowText("Enemies", 720, 134);
    gfx.ShowText("Left", 720, 144);
    gfx.ClearScreen(720, 164, 16, 16);
    gfx.ShowText(str , 720, 164);

}
