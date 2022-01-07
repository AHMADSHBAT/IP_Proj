#include "Obstacle.hpp"
#include "Obj.hpp"
#include "Pos.hpp"
#include <SDL.h>

Obstacle::Obstacle(Pos p_pos, SDL_Texture* p_tex)
:Obj(p_pos, p_tex)
{
}