#ifndef game_INCLUDED
#define game_INCLUDED
#define BH 32
#define BW 32
#define TH 28
#define TW 28
#define FW 25
#define FH 18
#define TotalEnemies 20
#include <SDL.h>
#include <string>
#include "MersenneTwister.h"

class Tank;
class Blocks;
class Bullet;
//template <class T>
class Frame;
class AIFG;
class GoodTank;
class EnemyTank;
struct MTRand;

class Tank {
    protected:
        float dx, dy;
        int xdirection, ydirection;
        bool backoff;
        bool motion;
        float x, prev_x;
        float y, prev_y;
        int size_w, size_h;
        bool active;

    public:
        Tank();
        Tank(int );
        Tank(float, float);
        Tank(float);
        int GetXDirection() { return xdirection;}
        int GetYDirection() { return ydirection;}
        int CheckPosition(Blocks bk);
        int CheckCollide(GoodTank);
        int CheckCollide(EnemyTank);
        bool IsActive();

        friend class Bullet;
};

class GoodTank : public Tank {
    private:
        int TankNo, life;
        SDL_Rect clip;
    public:

        GoodTank(int i) : Tank(i) { life = 6; TankNo = i; clip.x = 0; clip.y = 0; clip.w = TW; clip.h = TH;}
        void UpdateCord();
        int GetLife() { return life; }
        void ResetPosition(int, Bullet &);

        //template <class T>
        friend class Frame;
        friend class EnemyTank;
};

struct spawn_pos {
    float x, y;
    static int s_no;
    spawn_pos();

};

class EnemyTank : public Tank {
    private:
        int level, lapse;
        int storex, storey, tmpstorex, tmpstorey;
        static int TankPos;
        SDL_Rect clip;
        static int position;
        spawn_pos sp;
        int CoolDown, storecooltime;
        Uint16 intelligence;
        static int priority[3];
        static int resetPriority;
        static int Remaining;

    public:
        EnemyTank() { }
        EnemyTank(int);
        int CountDown();
        static int GetRemaining();
        void SetCount(int);
        void SortMove(GoodTank, GoodTank,int);
        int SelectMove(int);
        int UpdateCord(void);
        int Align(Blocks);
        void ResetPosition(GoodTank, GoodTank, EnemyTank[], Bullet[], int,int);
        void ResetPosition(int);

        //template <class T>
        friend class Frame;
};

class Blocks {
    private:
        SDL_Rect clip;
        int size_w, size_h;
        //int direction;

    public:
        int field[FH][FW];
        int life[FW][FH];
        Blocks();
        void LoadMap(int map_no);
        void RenderMap();
        //friend class Frame;
};

class Bullet {
    private:
        int NumBullets, RecoilTime, limit;
        float dx, dy;
        bool endPath, firsttime, onPath, Wait;
        int xdir, ydir;
        bool Collison;
        int level;
        int size_w, size_h;
        bool active1, active2;

    public:
        float x, y, prev_x, prev_y;
        int renderon;
        Bullet();
        Bullet(int);
        int GetOnPath();
        int GetEndPath();
        bool IsActive() {return active2;}
        void ResetAttrib();
        void SetTrigger(GoodTank);
        void SetTrigger(EnemyTank);
        void UpdateBullet(Blocks *bk);
        void BulletSound();
        int CheckCollide(GoodTank);
        int CheckCollide(EnemyTank, bool);
        void BlackTime();

        friend class Frame;
        friend class GoodTank;
        friend class EnemyTank;
};

//template <class T>
class Frame {
    SDL_Rect clip;

    public:
    Frame() {clip.x = 0; clip.y = 0; clip.h = BH; clip.w = BW;}
    void Blit(GoodTank);
    void Blit(EnemyTank);
    void Blit(Bullet);
    void ShowLife(int, int);
    void SelectiveRender(Blocks, Bullet);
    void SelectiveRender(Blocks, GoodTank);
    void SelectiveRender(Blocks, EnemyTank);

};

class AIFG {
    public:

    private:

    //will be ritten latter
};

#endif
