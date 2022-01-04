#include "Obstacle.hpp"
#include "Obj.hpp"
#include "Pos.hpp"
#include <SDL.h>

Obstacle::Obstacle(Vector2f p_pos, SDL_Texture* p_tex)
:Entity(p_pos, p_tex)
{
}