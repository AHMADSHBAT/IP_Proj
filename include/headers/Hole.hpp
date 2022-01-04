#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <Obj.hpp>
#include <Pos.hpp>

class Hole : public Obj
{
    public: 
    Hole(Pos p_pos, SDL_Texture* p_tex);
};