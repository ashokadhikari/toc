#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

class GameCore {
    private:
    SDL_Surface* welcome;
    SDL_Surface* pointer;
    SDL_Surface* BackGround;
    SDL_Surface* level;
    SDL_Surface* instr;
    SDL_Surface* credits;

    public:
    GameCore();
    ~GameCore();

    void ShowStatus(int, int);
    int Menu();
    void Play(int);
    void Instructions();
    void Credits();
    void Quit();
};

#endif // MENU_H_INCLUDED
