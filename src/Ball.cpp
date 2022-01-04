#include "Ball.hpp"
#include "Obj.hpp"
#include "Pos.hpp"
#include "Obstacle.hpp"
#include "Hole.hpp"

#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>


Ball::Ball(Pos p_pos, SDL_Texture* p_tex, SDL_Texture* p_powerMTexBG, int p_index)
:Obj(p_pos, p_tex)
{
    index = p_index;
    powerBar = Obj(Pos(-64, -64), p_powerMTexBG);
}

void Ball::setVelocity(float x, float y)
{
    velocity.X = x;
    velocity.Y = y;
}

void Ball::setLaunchedVelocity(float x, float y)
{
    launchedVelocity.X = x;
    launchedVelocity.Y = y;
}

void Ball::setInitialMousePos(float x, float y)
{
    initialMousePos.X = x;
    initialMousePos.Y = y;
}

void Ball::setWin(bool p_win)
{
    win = p_win;
}

