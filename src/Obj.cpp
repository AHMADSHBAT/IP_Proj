#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <Obj.hpp>


Obj::Obj(Pos p_pos, SDL_Texture* p_tex)
:pos(p_pos), tex(p_tex)
{
	currentFrame.x = 0;
	currentFrame.y = 0;
	currentFrame.w = 32;
	currentFrame.h = 32;
	SDL_QueryTexture(p_tex, NULL, NULL, &currentFrame.w, &currentFrame.h);
}
Obj::Obj(){};

SDL_Texture* Obj::getTex()
{
	return tex;
}

void Obj::update(double deltaTime)
{

}

void Obj::setPos(float x, float y)
{
	pos.x = x;
	pos.y = y;
}

void Obj::setAngle(float p_angle)
{
	angle = p_angle;
}

void Obj::setScale(float w, float h)
{
	scale.x = w;
	scale.y = h;
}

SDL_Rect Obj::getCurrentFrame()
{
	return currentFrame;
}