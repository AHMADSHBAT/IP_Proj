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

SDL_Texture * MainWin::loadTexture(char * p_filePath, const int & index)
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

void MainWin::loadTexture(Entity & entity)
{
    SDL_Rect src = entity.getRect();
    SDL_Rect dst;
    dst.x = entity.getPosition().X + (entity.getRect().w - entity.getRect().w * entity.getScale().second) / 2;
    dst.y = entity.getPosition().Y + (entity.getRect().h - entity.getRect().h * entity.getScale().first) / 2;
    dst.w = entity.getRect().w * entity.getScale().second;
    dst.h = entity.getRect().h * entity.getScale().first;

    SDL_RenderCopyEx(m_rend, entity.getTexture(),&src, &dst, entity.getAngle(), 0, SDL_FLIP_NONE);

}

void MainWin::loadTexture(int x, int y, TexPtr tex)
{
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.y;
    rect.h;


    SDL_Rect dst;
    dst.x = x; dst.y = y;
    dst.w = rect.w;
    dst.h = rect.h;

    SDL_RenderCopy(m_rend, tex, &rect, &dst);
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
