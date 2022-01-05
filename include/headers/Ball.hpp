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
	Ball(Pos p_pos, SDL_Texture* p_tex, SDL_Texture* p_powerMTexBG, int p_index);
    void setWin(bool p_win);
    void setInitialMousePos(float x, float y);
    void setVelocity(float x, float y);
    void setLaunchedVelocity(float x, float y);
    Pos velocity;
    Pos target;
    Pos launchedVelocity;
    float velocity1D;
    float launchedVelocity1D;
    Pos initialMousePos;
    bool canMove = true;
    bool playedSwingFx = true;
    int index;
    int strokes = 0;
    int dirX = 1;
    int dirY = 1;
    bool win = false;
    float friction = 0.001;
    Obj powerBar;
};
