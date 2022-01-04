#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <Obj.hpp>
#include <Pos.hpp>

class Obstacle : public Obj
{
    public: 
    Obstacle(Pos p_pos, SDL_Texture* p_tex);

    private:
};