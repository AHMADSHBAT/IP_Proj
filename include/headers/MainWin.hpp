#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <utility>
#include <Entity.hpp>

typedef SDL_Texture* TexPtr;


class MainWin
{
public:
    MainWin(char *,int ,int);
    SDL_Texture * loadTexture(char *, const int &);
    void loadTexture(Entity & entity);
    void loadTexture(int, int, TexPtr);
    void rendererClear();
    void render(SDL_Texture *);
    void display();

    


    ~MainWin();

    private:
    SDL_Window * m_win;
    SDL_Renderer * m_rend;
    ~MainWin();

};