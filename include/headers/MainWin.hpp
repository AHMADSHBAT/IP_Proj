#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <utility>



class MainWin
{
public:
    MainWin(char *,int ,int);
    SDL_Texture * LoadTexture(char *, const int &);
    void rendererClear();
    void render(SDL_Texture *);
    void display();

    


    ~MainWin();

    private:
    SDL_Window * m_win;
    SDL_Renderer * m_rend;
    ~MainWin();

};