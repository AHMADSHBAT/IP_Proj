#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <vector>
#include <Hole.hpp>
#include <Obstacle.hpp>

#include <Obj.hpp>
#include <Pos.hpp>

class Ball : public Obj
{
public:
	Ball(Pos p_pos, SDL_Texture* p_tex, SDL_Texture* p_pointTex, SDL_Texture* p_powerMTexFG, SDL_Texture* p_powerMTexBG, int p_index);
    Pos& getVelocity()
	{
		return velocity;
	}
    Pos& getInitialMousePos()
	{
		return initialMousePos;
	}
    std::vector<Obj> getPoints()
	{
		return lunchPower;
	}
    std::vector<Obj> getPowerBar()
	{
		return powerBar;
	}
    int getStrokes()
    {
        return strokes;
    }
    bool  isWin ()
    {
        return win;
    }
    void setWin(bool p_win);
    void setInitialMousePos(float x, float y);
    void setVelocity(float x, float y);
    void setLaunchedVelocity(float x, float y);
    void update(double deltaTime, bool mouseDown, bool mousePressed, std::vector<Obstacle> Obstacles, std::vector<Hole> holes);
private:
    Pos velocity;
    Pos holePos;
    Pos launchedVelocity;
    Pos initialMousePos;
    float velocity1D;
    float launchedVelocity1D;
    bool canMove = true;
    int index;
    int strokes = 0;
    int dirX = 1 ;
    int dirY = 1;
    bool win = false;
    float friction = 0.0005f;
    std::vector<Obj> lunchPower;
    std::vector<Obj> powerBar;
};