#include "game.h"
#include "sGraphics.h"
#include "sInput.h"
#include "sSound.h"
#include "globals.h"
#include <conio.h>
#include <fstream>
#include <iostream>
#include <string>
#define PTank 50
#define PEagle 50

using namespace std;
enum blocktypes {GRASS = 1, TRANSPARENT, EAGLE, UNBREAKABLE, BREAKABLE};
enum directions {LEFT = -1, UP = -1, RIGHT = 1, DOWN = 1, NOT = 0};
enum cliptype {CLIPGRASS = 0, CLIPTRANS, CLIPEAGLE, CLIPUNBREAK, CLIPBREAK, CLIPBREAK_1, CLIPBREAK_2 };
enum cliptype_tank {C_DOWN = 0, C_UP, C_LEFT, C_RIGHT};
enum moves { MDOWN = 0, MUP, MLEFT, MRIGHT};

int map_id = 1;
int EnemyTank::position = 0;
int spawn_pos::s_no = 0;

spawn_pos::spawn_pos() {
    y = 0;
    x = BW * 3 + (s_no%4) * 6 * BW;
    cout << x <<" ";
    s_no++;
}

EnemyTank::EnemyTank(int inte) {
    //position = (position++ % 3);
    Tank::x = sp.x;
    Tank::y = sp.y;
    CoolDown = 0;
    storecooltime = 5000;
    intelligence = inte;
    tmpstorex = storex = 300; tmpstorey = storey = 300;

    clip.x = 0 * TW; clip.y = 1 * TH;
    clip.w = TW; clip.h = TH;

    for(int i = 0; i < 3; i++) {
        if(i == 0) priority[i] = 100;
            else priority[i] = 350;
    }
}

int EnemyTank::CountDown() {
    if(CoolDown == 0) { CoolDown = storecooltime; return 1;}
    CoolDown--;
    return 0;
}

void EnemyTank::SetCount(int cnt) {
    CoolDown = cnt;
}

void EnemyTank::SortMove(GoodTank gt1, GoodTank gt2,int current) {
    int relx[3], rely[3], value[3];

    int x = mtrandl.randInt(5);
    if(x < intelligence) {
    resetPriority++;
    relx[1] = (int) (x - gt1.x);
    rely[1] = (int) (y - gt1.y);

    if(dble) {
    relx[2] = (int) (x - gt2.x);
    rely[2] = (int) (y - gt2.y);
    }
    relx[0] = (int) (x - 12 * BW);
    rely[0] = (int) (y - 17 * BH);

    for(int i = 0; i < NumPlayers + 1; i++) value[i] = abs(relx[i]) + abs(rely[i]) + priority[i];

    int small = value[0];
    int which = 0;
    for(int i = 0; i < NumPlayers + 1; i++) {
        if(value[i] < small) {small = value[i]; which = i;}
    }

    if(which == 0)
    priority[which]+=PEagle;//in multiple enemies
    else priority[which]+=PTank;

    if(which == 1) {storex = ((int)gt1.x / 32) * 32; storey = ((int)gt1.y / 32) * 32;}
    if(which == 2) {storex = ((int)gt2.x / 32) * 32; storey = ((int)gt2.y / 32) * 32;}
    if(which == 0) {storex = 12 * BW; storey = 17 * BW;}
    }
    else {
        storex = mtrandl.randInt(BW * 18) + 3 * BW; storex = (storex / 32) * 32;
        storey = mtrandl.randInt(BH * 17) ; storey = (storey / 32) * 32;
    }

    if(resetPriority == current) {
        resetPriority = 0;
        for(int i = 0; i < 3; i++) {
            if(i == 0) priority[i] = 100;
            else priority[i] = 350;
    }
    }
}



int EnemyTank::UpdateCord(void) {
    prev_x = x;
    prev_y = y;
    int ix = (int) x;
    int iy = (int) y;

    //int path = mtrandl.randInt(1);
    int path = 0;
    if(path = 1) {
    if((ix - storex) < 0 ) {
        x += dx; clip.x = MRIGHT * TW;
        xdirection = RIGHT; ydirection = NOT;
    }
    if((ix - storex) > 0 ) {
        x -= dx; clip.x = MLEFT * TW;
        xdirection = LEFT; ydirection = NOT;
    }

    if((ix - storex) == 0) {
        if((iy - storey) < 0) {
            y += dy; clip.x = MDOWN * TW;
            xdirection = NOT; ydirection = DOWN;
        }

        if((iy - storey) > 0) {
            y -= dy; clip.x = MUP * TW;
            xdirection = NOT; ydirection = UP;
        }

        if((iy - storey) == 0) {
           return 0;
        }

    }
    }

    if(path == 0) {
    if((iy - storey) < 0 ) {
        y += dy; clip.x = MDOWN * TW;
        ydirection = DOWN; xdirection = NOT;
    }
    if((iy - storey) > 0 ) {
        y -= dy; clip.x = MUP * TW;
        xdirection = NOT; ydirection = UP;
    }

    if((iy - storey) == 0) {
        if((ix - storex) < 0) {
            x += dx; clip.x = MRIGHT * TW;
            xdirection = RIGHT; ydirection = NOT;
        }

        if((ix - storex) > 0) {
            x -= dx; clip.x = MLEFT * TW;
            xdirection = LEFT; ydirection = NOT;
        }

        if((ix - storex) == 0) {
           return 0;
        }


    }
    }

    return 1;
}

int EnemyTank::Align(Blocks bk) {
    prev_x = x;
    prev_y = y;
    int fx = (int)x / BW, fy = (int)y / BH;
    int m = 1,p = 1;

    for(int i = 0; i < 4; i ++) {
        if(i % 2) p = -p;
        else m = -m;
        if(bk.field[fy + p][fx + m] == BREAKABLE || GRASS || 0 ) {
            tmpstorex = (fx + m) * BW;
            tmpstorey = (fy + p) * BH;
            break;
        }
    }

    if(m == 1) {
        x += dx; clip.x = MRIGHT * TW;
        xdirection = RIGHT; ydirection = NOT;

        if((int)x - tmpstorex == 0) return 1;
    }

    if(m == -1) {
        x -= dx; clip.x = MLEFT * TW;
        xdirection = LEFT; ydirection = NOT;
        if((int)x - tmpstorex == 0) return 1;
    }

    if(p == 1) {
        y += dy; clip.x = MDOWN * TW;
        xdirection = NOT; ydirection = DOWN;
        if((int)y - tmpstorey == 0) return 1;
    }

    if(p == -1) {
        y += dy; clip.x = MUP * TW;
        xdirection = NOT; ydirection = UP;
        if((int)y - tmpstorey == 0) return 1;
    }
    return 0;
}

int EnemyTank::Remaining = TotalEnemies;
void EnemyTank::ResetPosition(GoodTank tk1, GoodTank tk2, EnemyTank et[], Bullet bt[], int currentnum, int currentenemy) {
    bool flag[4] = {false};

    static int z;

    Remaining--;
    if(Remaining == 0) {Level_Complete = true;map_id++;}
    if(Remaining < 4) {active = false; bt[currentnum].active1 = true;}


    for(int i = 0; i < currentenemy; i++) {

    prev_x = x = (3 + 6 * i) * BW;
    prev_y = y = 0;
    if(CheckCollide(tk1)) {flag[i] = true; continue;}
    if(dble and CheckCollide(tk2)) {flag[i] = true; continue;}
    for(int j = 0; j < currentenemy; j++) {

        if(j != currentnum)
        if(CheckCollide(et[j])) {flag[i] = true; continue;}
    }

}

    for(int i = 0; i < currentenemy; i++) {
        if(flag[i]) continue;
        prev_x = x = (3 + 6 * i) * BW;
        prev_y = y = 0;
        break;
    }
    if(!flag[0] & !flag[1] & !flag[2] & !flag[3]) {
        prev_x = x = sp.x;
        prev_y = y = sp.y;
    }
    z = (z + 1) % 4;
    clip.y = z * TH;

}

void EnemyTank::ResetPosition(int i) {
    Remaining = TotalEnemies;

    prev_x = x = (3 + 6 * i) * BW;
    prev_y = y = 0;

    xdirection = NOT;
    ydirection = DOWN;
    size_w = TW ;size_h = TH;
    active = true;

}
void GoodTank::ResetPosition(int cord, Bullet &bt) {
    prev_x = x = (9 + 5 * cord)* BH;
    prev_y = y = 17 * BW;
    clip.x = MUP * TH;
    life--;  if(life == 0) {active = false; bt.active2 = false;}
}

int EnemyTank::GetRemaining() {
    return Remaining;
}
