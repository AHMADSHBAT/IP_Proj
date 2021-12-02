#include <Ball.hpp>
#include <SDL.h>
#include <SDL_image.h>




Ball::Ball(Pos & pos, bool m)
{
    ballPos = pos;
    moving = m;
}


bool Ball::pullTheBall(Pos & p, float a, SDL_Event * e)
{
    Pos newP = {0, 0};
    float distance = 0;
    float angle = 0;
    if(e->button.button == SDL_BUTTON_LEFT)
    {
        while(e->type == SDL_MOUSEBUTTONDOWN)
        {
            while(e->button.button != SDL_RELEASED)
            {

            }   
        }
    }
}