#pragma once
#include <Pos.hpp>
#include <iostream>
#include <SDL_image.h>
#include <SDL.h>



class Entity
{
    public:
        Entity(Pos &, SDL_Texture *, char *);

        std::pair<float, float> getScale() const { return scale; }

        float getAngle() const { return angle; }

        SDL_Rect getRect() const { return rect; }

        Pos getPosition() const { return pos;}

        void setPosition(Pos p) { pos = p;}

        void setAngle(float angle) { angle = angle;}

        void setScale(std::pair<float, float> pair) { scale = pair;}
        


    ~Entity(){};


    private:
        char* name;
        SDL_Texture * texture;
        Pos pos;
        float angle;
        std::pair<float, float> scale{1.0f, 1.0f};
        SDL_Rect rect;


};