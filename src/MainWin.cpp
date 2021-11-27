#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <MainWin.hpp>


MainWin::MainWin(char * p_title, int p_weidth, int p_hight)
    :m_win(0), m_rend(0)
{
    m_win = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_weidth, p_hight, SDL_WINDOW_SHOWN);
    if(m_win == 0)
        std::cout << "error in MainWin constructor win ptr\n";

    m_rend = SDL_CreateRenderer(m_win, -1, 0);
    if(m_rend == 0)
        std::cout << "error in rend ptr\n";
    

}

SDL_Texture * MainWin::LoadTexture(char * p_filePath, const int & index)
{
    SDL_Texture * newTexture = 0;
    newTexture = IMG_LoadTexture(m_rend, p_filePath);
    if(newTexture == 0)
    {
        std::cout << "error with LoadTexture func\n";
        return 0;
    }
    std::cout << "texture " << p_filePath << " has been loaded successfully\n";
    
    return newTexture; 

}

SDL_Texture * MainWin::LoadTexture(Entity & entity)
{
    SDL_Rect rect = entity.getRect();

}



void MainWin::rendererClear() 
{
    SDL_RenderClear(m_rend);
}


void MainWin::render(SDL_Texture * p_texture) 
{
    SDL_RenderCopy(m_rend, p_texture, 0, 0);
}


void MainWin::display()
{
    SDL_RenderPresent(m_rend);
}


MainWin::~MainWin()
{
    SDL_DestroyWindow(m_win);
}
