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
#include "globals.h"
#include "MersenneTwister.h"
#include <iostream>
#include <string>
#define TotalEnemies 20
#include "menu.h"

using namespace std;
bool Level_Complete = true;
const int MaxEnemy = 4;
int NumPlayers;
bool dble;

void GameCore::Play(int num) {

    gfx.SetBgColor(0,0,0);
    GoodTank tk2(2), tk1(1);
    EnemyTank et[MaxEnemy] = {3, 3, 4, 4};

    Bullet bt[MaxEnemy] = {300, 200, 500, 400} ;

    Blocks bk;
    Bullet bullet1(100), bullet2(100);
    Frame onscreen;

    map_id = 1;


    NumPlayers = num;
    gameover = false;

   do {
    Mix_Music *music = sfx.LoadMusic("sfx/alone.mp3");
    sfx.AdjustVolume(sample, 20);
    sfx.AdjustVolume(80);
    sfx.PlayMusic(music, -1);             //////next stage

    for(int j = 0; j < gfx.screen -> h / BH; j++)
            for(int i = 0; i < gfx.screen -> w / BW; i++) {
                bk.field[j][i] = 0;
                bk.life[j][i] = 1;
            }
    bk.LoadMap(map_id);
    bk.RenderMap();

    bool *keystate = in.GetKeyState();
    int currentEnemy = 4;
    bool set1 = 0, set2 = 0, set3 = 0, set4 = 0, set5 = 0, isOk = 1, dummy;
    bool flag = false;
    if(NumPlayers == 2) dble = true;
    else dble = false;

    tk1.ResetPosition(0, bullet1);
    if(dble) tk2.ResetPosition(1, bullet2);


    for(int h = 0; h < currentEnemy; h++) et[h].ResetPosition(h);
    for(int h = 0; h < currentEnemy; h++) bt[h].ResetAttrib();



    int kill1 = 0, kill2 = 0;
   Level_Complete = false;
    while (!gameover and !Level_Complete)
    {

        in.ProcessEvents();

        if (keystate[SDLK_p])
        {
            gfx.Wait(200);
            gfx.SetTextColor(0,255,0);

            in.ProcessEvents();
            while(!keystate[SDLK_p]) {
                in.ProcessEvents();
                gfx.ShowText("GAME PAUSED",700,300);
                gfx.FlipDrawing();
            }
            gfx.Wait(200);
            gfx.ClearScreen( 700 , 300,176, 16);
            in.ProcessEvents();

        }

        if (in.QuitRequest())
        {
            exit(1);
            continue;
        }
        if (keystate[SDLK_RCTRL]) bullet1.SetTrigger(tk1);
        if (keystate[SDLK_SPACE]) bullet2.SetTrigger(tk2);


//updating tank******tank 1************************************************
        if(tk1.IsActive()) {
        tk1.UpdateCord();
        tk1.CheckPosition(bk);
        if(dble) tk1.CheckCollide(tk2);
        for (int i = 0; i < currentEnemy; i++)
            if(et[i].IsActive()) tk1.CheckCollide(et[i]);
        onscreen.SelectiveRender(bk, tk1);
        }

//..............for tank 2.......................................

        if(dble) {
        if(tk2.IsActive()) {
        tk2.UpdateCord();
        tk2.CheckPosition(bk);
        tk2.CheckCollide(tk1);
        for (int i = 0; i < currentEnemy; i++)
            if(et[i].IsActive()) tk2.CheckCollide(et[i]);
        onscreen.SelectiveRender(bk, tk2);
        }
        }
//updating bullet*******if space is pressed******for tank 1*****************************************

        if(tk1.IsActive()) {
        if (bullet1.renderon || bullet1.GetOnPath())
        {
            onscreen.SelectiveRender(bk, bullet1);
            if (bullet1.renderon) bullet1.renderon--;
        }
        if (bullet1.GetOnPath())
        {
            bullet1.UpdateBullet(&bk);
            if(dble) bullet1.CheckCollide(tk2);
            dummy = true;
            for (int i = 0; i < currentEnemy; i++)
            {
                if (et[i].IsActive()) {
                if (bullet1.CheckCollide(et[i], dummy))
                {
                    kill1++;
                    onscreen.SelectiveRender(bk,et[i]);

                    et[i].ResetPosition(tk1, tk2, et, bt, i, currentEnemy);

                }

                }
            }
            bullet1.BulletSound();
            onscreen.Blit(bullet1);

        }

        bullet1.BlackTime();
        }
        /* FOR tank 2 bullet 2.........................................................................*/
        if(dble) {
        if(tk2.IsActive()) {
        if (bullet2.renderon || bullet2.GetOnPath())
        {
            onscreen.SelectiveRender(bk, bullet2);
            if (bullet2.renderon) bullet2.renderon--;
        }
        if (bullet2.GetOnPath())
        {
            bullet2.UpdateBullet(&bk);
            bullet2.CheckCollide(tk1);
            for (int i = 0; i < currentEnemy; i++)
            {
                if (et[i].IsActive()) {
                if(bullet2.CheckCollide(et[i], dummy))
                {
                    kill2++;
                    onscreen.SelectiveRender(bk,et[i]);
                    et[i].ResetPosition(tk1, tk2, et, bt, i, currentEnemy);
                }
            }
            }
            bullet2.BulletSound();
            onscreen.Blit(bullet2);


        }
        bullet2.BlackTime();
        }
        }
//*******************************************************************

        dummy = false;
        for (int i = 0; i < currentEnemy; i++)
        {
            if(bt[i].IsActive() or bt[i].renderon) {
            bt[i].SetTrigger(et[i]);

            if (bt[i].renderon || bt[i].GetOnPath())
            {
                onscreen.SelectiveRender(bk, bt[i]);
                if (bt[i].renderon) bt[i].renderon--;
            }
            }
            if(bt[i].IsActive()) {
            if (bt[i].GetOnPath())
            {
                bt[i].UpdateBullet(&bk);
                if (bt[i].CheckCollide(tk1)) if(tk1.IsActive()) tk1.ResetPosition(0, bullet1);
                if(dble and bt[i].CheckCollide(tk2)) if(tk2.IsActive()) tk2.ResetPosition(1, bullet2);
                for (int j = 0; j < currentEnemy; j++)
                    if (i != j) bt[i].CheckCollide(et[j], dummy);
                bt[i].BulletSound();  //for bullet
                onscreen.Blit(bt[i]);
            }
            bt[i].BlackTime();

            }
            if(et[i].IsActive()) {
            if (et[i].CountDown())
            {
                et[i].SortMove(tk1, tk2, currentEnemy);
                set1 = false;
                set3 = false;
                flag = false;
            }

            if (isOk) set1 = et[i].UpdateCord();
            if (!set1) et[i].SetCount(0);

            set2 = et[i].CheckPosition(bk);
            set4 = et[i].CheckCollide(tk1);
            if(dble) set5 = et[i].CheckCollide(tk2);
            for (int j = 0; j < currentEnemy; j++)
            {
                if (i != j)
                {
                    set3 = et[i].CheckCollide(et[j]);
                    if (set3) et[i].SetCount(0);
                }
            }

            if (set4 or set5) et[i].SetCount(0);
            if (flag == true) set2 = 0;
            if (set2)
            {
                et[i].SetCount(0);
                flag = true;
            }
            onscreen.SelectiveRender(bk,et[i]);
        }
        }
        for (int i = 0; i < currentEnemy; i++) {
            if(et[i].IsActive())
            onscreen.Blit(et[i]);
        }

        if(dble and tk2.IsActive()) onscreen.Blit(tk2);
        if(tk1.IsActive()) onscreen.Blit(tk1);

        onscreen.ShowLife(tk1.GetLife(), tk2.GetLife());

        if(dble) {
            if(!tk1.IsActive() and !tk2.IsActive()) gameover = true;
        }
        else {
            if(!tk1.IsActive()) gameover = true;
        }

    gfx.FlipDrawing();

    }

    ShowStatus(kill1, kill2);
    sfx.StopMusic();
    sfx.FreeMusic(music);
    gfx.ClearScreen();
    gfx.FlipDrawing();
    //while(!keystate[SDLK_RETURN]) {}

   }

    while(!gameover);


}
GameCore::GameCore() {
    welcome = gfx.LoadImage("gfx/EnemyTanks.png");
    pointer = gfx.LoadImageAlpha("gfx/menu/Pointer.png" );
    BackGround = gfx.LoadImageAlpha("gfx/menu/MenuScreen1.png");
    level = gfx.LoadImageAlpha("gfx/menu/ScoreBoard.png");
    instr = gfx.LoadImageAlpha("gfx/menu/Instructions.png");
    credits = gfx.LoadImageAlpha("gfx/menu/Credits.png");
}
GameCore::~GameCore(){
    gfx.FreeImage(welcome);
    gfx.FreeImage(pointer);
    gfx.FreeImage(BackGround);
    gfx.FreeImage(level);
    gfx.FreeImage(instr);
    gfx.FreeImage(credits);

}


int GameCore::Menu() {

    bool *keystate = in.GetKeyState();
    int Result = 0;
    int x = 74;
    int y = 180;
    bool out = true;
    while(out){
    gfx.ClearScreen();
    gfx.PutImage(BackGround,0,0);
    gfx.PutImage(pointer, x, y);
    in.ProcessEvents();
    if(keystate[SDLK_DOWN]){
        Result = (Result+1)%5;
    }
    if(keystate[SDLK_UP])   {Result = (Result-1 + 5)%5;}
    if(keystate[SDLK_RETURN])   out = false;
    y = 180+ Result * 60;
    gfx.FlipDrawing();
    gfx.Wait(50);
    }
    gfx.ClearScreen();
    return (Result+1);
    //return 1;
}

void GameCore::ShowStatus(int kill1, int kill2) {
            bool out = true;
            char str[20];

            gfx.PutImage(level, 200, 200);
            gfx.ShowText("Number Killed", 300, 220);
            gfx.ShowText("Score", 450, 220);
            gfx.ShowText("Total", 500, 220);


            gfx.ShowText("Player1", 220, 250);
            sprintf(str, "%d", kill1);
            gfx.ShowText(str, 300, 250);
            gfx.ShowText("50", 450, 250);
            sprintf(str, "%d", kill1 * 50);
            gfx.ShowText(str, 500, 250);

           if(dble) {
            gfx.ShowText("Player2", 220, 300);
            sprintf(str, "%d", kill2);
            gfx.ShowText(str, 300, 300);
            gfx.ShowText("50", 450, 300);
            sprintf(str, "%d", kill2 * 50);
            gfx.ShowText(str, 500, 300);
           }

            gfx.ShowText("Press o to Proceed", 300, 370);

            gfx.FlipDrawing();

            bool *keystate = in.GetKeyState();
            while(out) {
                in.ProcessEvents();
                if(keystate[SDLK_o]) out = false;
            }
}

void GameCore::Instructions() {
       bool* keystate = in.GetKeyState();
       bool  out = true;
       gfx.PutImage(instr,0,0 );
        gfx.FlipDrawing();
        while(out) {
                in.ProcessEvents();
                if(keystate[SDLK_ESCAPE]) out = false;
            }
            in.ProcessEvents();
}

void GameCore::Credits() {
        bool out = true;
       bool* keystate = in.GetKeyState();
       gfx.PutImage(credits,0,0 );
        gfx.FlipDrawing();
        while(out) {
                in.ProcessEvents();
                if(keystate[SDLK_ESCAPE]) out = false;
            }
            in.ProcessEvents();
}

