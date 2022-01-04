#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <Pos.hpp>


class Obj
{
public:
	Obj(Pos p_pos, SDL_Texture* p_tex);
    Obj();
    Pos& getPos()
	{
		return pos;
	}
	float getAngle()
	{
		return angle;
	}
	Pos getScale()
	{
		return scale;
	}
	void setPos(float x, float y);
	void setScale(float w, float h);
	void setAngle(float angle);
	SDL_Texture* getTex();
	void update(double deltaTime);
	SDL_Rect getCurrentFrame();
	Pos pos;
	float angle = 0;
	Pos scale = Pos(1, 1);
	SDL_Rect currentFrame;
	SDL_Texture* tex;
};