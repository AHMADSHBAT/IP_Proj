#pragma once
#include <SDL.h>
#include <SDL_image.h>


typedef SDL_Texture* TexPtr;

class Pos
{
    public:
        Pos();
        Pos(float x, float y);


        float X, Y;


        void PosPrint();

        ~Pos();
 
};