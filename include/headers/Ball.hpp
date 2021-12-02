#pragma once
#include <Pos.hpp>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>



class Ball
{
    public:
        Ball(Pos &, bool);

        bool pullTheBall(Pos & p, float a, SDL_Event *);

        Pos & getPosition()
        {
            return ballPos;
        }
        float getAngle()
        {
            return angle;
        }
        float getDistance()
        {
            return distance;
        }
        bool ballIsMoving()
        {
            return moving;
        }



    private:
        bool moving;
        float angle;
        float distance;
        Pos mousePos;
        Pos ballPos;
        TexPtr tex;


};


