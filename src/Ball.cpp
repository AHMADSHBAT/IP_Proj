#include "Ball.hpp"
#include "Obj.hpp"
#include "Pos.hpp"
#include "Obstacle.hpp"
#include "Hole.hpp"

#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>


Ball::Ball(Pos p_pos, SDL_Texture* p_tex, SDL_Texture* p_pointTex, SDL_Texture* p_powerMTexFG, SDL_Texture* p_powerMTexBG, int p_index)
:Obj(p_pos, p_tex)
{
    index = p_index;
    lunchPower.push_back(Obj(Pos(-64, -64), p_pointTex));
    powerBar.push_back(Obj(Pos(-64, -64), p_powerMTexBG));
    powerBar.push_back(Obj(Pos(-64, -64), p_powerMTexFG));
}

void Ball::setVelocity(float x, float y)
{
    velocity.x = x;
    velocity. y = y;
}

void Ball::setLaunchedVelocity(float x, float y)
{
    launchedVelocity.x = x;
    launchedVelocity. y = y;
}

void Ball::setInitialMousePos(float x, float y)
{
    initialMousePos.x = x;
    initialMousePos. y = y;
}

void Ball::setWin(bool p_win)
{
    win = p_win;
}

void Ball::update(double deltaTime, bool mouseDown, bool mousePressed, std::vector<Obstacle> Obstacles,std::vector<Hole> holes)
{   
    /* when the ball set to win, then the following code block should make the ball appears to fall down in the hole. */
    if (win)
    {
        if (getPos().x < holePos.x)
        {
            setPos(getPos().x += 0.1*deltaTime, getPos().y);
        }
        else if (getPos().x > holePos.x)
        {
            setPos(getPos().x -= 0.1*deltaTime, getPos().y);
        }
        if (getPos().y < holePos.y)
        {
            setPos(getPos().x, getPos().y += 0.1*deltaTime);
        }
        else if (getPos().y > holePos.y)
        {
            setPos(getPos().x, getPos().y -= 0.1*deltaTime);
        }
        setScale ( getScale (). x - 0.001 * deltaTime, getScale (). y - 0.001 * deltaTime);
        return;
    }
    /* make lets say form the hole side checking if the ball is close enough to the hole itself, then set the current ball a win */
    for (Hole h : holes)
    {
        if (getPos().x + 4 > h.getPos().x && getPos().x + 16 < h.getPos().x + 20 && getPos().y + 4 > h.getPos().y && getPos().y + 16 < h.getPos().y + 20)
        {
            setWin(true);
            holePos.x = h.getPos().x ;
            holePos.y = h.getPos().y + 3;
        }
    }

    /* saving the position of the mouse when the user pressing */
    if (mousePressed && canMove)
    {
        int mouseX = 0;
	    int mouseY = 0;
	    SDL_GetMouseState(&mouseX, &mouseY);
        setInitialMousePos(mouseX, mouseY);
    }

    /* */
    if (mouseDown && canMove)
    {
        
        int mouseX = 0;
	    int mouseY = 0;
	    SDL_GetMouseState(&mouseX, &mouseY);
        setVelocity ((mouseX - getInitialMousePos (). x ) / - 150 , (mouseY - getInitialMousePos (). y ) / - 150 );
        setLaunchedVelocity ((mouseX - getInitialMousePos (). x ) / - 150 , (mouseY - getInitialMousePos (). y ) / - 150 );
        velocity1D = SDL_sqrt((getVelocity().x) + abs(getVelocity().y));
        launchedVelocity1D = velocity1D;
 
        lunchPower.at(0).setPos(getPos().x, getPos().y + 8 - 32);
        lunchPower.at(0).setAngle(SDL_atan2(velocity.y, velocity.x)*(180/3.1415) + 90);

        dirX = velocity.x/abs(velocity.x);
        dirY = velocity.y/abs(velocity.y);
        /* setting the power bar on beside the ball */
        powerBar.at(0).setPos(getPos().x + 40, getPos().y - 32);
        powerBar.at(1).setPos(getPos().x + 44, getPos().y + 4 - 32*powerBar.at(1).getScale().y);
        if (velocity1D > 1)
        {
            velocity1D = 1;
            launchedVelocity1D = 1;
        }
        powerBar.at(1).setScale(1, velocity1D/1);
    }
    else
    {
        /* moving algorithm */
        lunchPower.at(0).setPos(-64, -64);
        powerBar.at(0).setPos(-64, -64);
        powerBar.at(1).setPos(-64, -64);
        canMove = false ;
        setPos ( getPos (). x + getVelocity (). x * deltaTime, getPos (). y + getVelocity (). y * deltaTime);
        if (getVelocity().x > 0.001 || getVelocity().x < -0.001 || getVelocity().y > 0.001 || getVelocity().y < -0.001)
        {
            if (velocity1D > 0)
            {
                velocity1D -= friction * deltaTime;
            }
            else
            {
                velocity1D = 0;
            }
            velocity.x = (velocity1D/launchedVelocity1D)*abs(launchedVelocity.x)*dirX;
            velocity.y = (velocity1D/launchedVelocity1D)*abs(launchedVelocity.y)*dirY;


        }
        else
        {
            setVelocity(0,0);
            int mouseX = 0;
	        int mouseY = 0;
            SDL_GetMouseState(&mouseX, &mouseY);
            setInitialMousePos(mouseX, mouseY);
            canMove = true;
        }
        /* to split the screen into two sides */
        if (getPos().x + getCurrentFrame().w > 640/(2 - index))
        {
            /* reversing the ball when it hits the right wall */
            setVelocity(-abs(getVelocity().x), getVelocity().y);
            dirX = -1;
        }
        else if (getPos().x < 0 + (index*320))
        {
            /* reversing the ball when it hits the left wall */
            setVelocity(abs(getVelocity().x), getVelocity().y);
            dirX = 1;
        }
        else if (getPos().y + getCurrentFrame().h > 480)
        {
            /* reversing the ball when it hits the bottom wall */
            setVelocity(getVelocity().x, -abs(getVelocity().y));
            dirY = - 1 ;
        }
        else if (getPos().y < 0)
        {
            /* reversing the ball when it hits the up wall */
            setVelocity(getVelocity().x, abs(getVelocity().y));
            dirY = 1 ;
        }
        /* reversing the ball if it his one of the obstacles */
        for (Obstacle& t : Obstacles)
	    { 
		    float newX = getPos().x + getVelocity().x*deltaTime;
            float newY = getPos ().y ;
            if (newX + 16 > t.getPos().x && newX < t.getPos().x + t.getCurrentFrame().w &&
                newY + 16 > t.getPos().y && newY < t.getPos().y + t.getCurrentFrame().h - 3)
            {
                setVelocity ( getVelocity (). x * - 1 , getVelocity (). y );
                dirX *= -1;
            }

            newX = getPos (). x ;
            newY = getPos (). y + getVelocity ().y * deltaTime;
            if (newX + 16 > t.getPos().x && newX < t.getPos().x + t.getCurrentFrame().w && newY + 16 > t.getPos().y && newY < t.getPos().y + t.getCurrentFrame().h - 3)
            {
                setVelocity ( getVelocity (). x , getVelocity (). y * - 1 );
                dirY *= - 1 ;
            }
	    }
    }
    
}