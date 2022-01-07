#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <iostream>
#include <vector>
#include <MainWin.hpp>
#include <Obj.hpp>
#include <Ball.hpp>
#include <Obstacle.hpp>
#include <Hole.hpp>
#include <SDL_ttf.h>

typedef enum
{
	G_TITLE = 0,
	G_GAME,
	G_END
} State;

bool  init ()
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;
	if (!(TTF_Init()))
		std::cout << "TTF_init has failed. Error: " << SDL_GetError() << std::endl;
	return true;
}

bool SDLinit = init();

MainWin window("IP_Project", 640, 480);

SDL_Texture* ballTexture = window.loadTexture("res/png/ball.png");
SDL_Texture* holeTexture = window.loadTexture("res/png/hole.png");
SDL_Texture* pointTexture = window.loadTexture("res/png/point.png");
SDL_Texture* ObstacleLightTexture32 = window.loadTexture("res/png/Obstacle32_light.png");
SDL_Texture* ObstacleLightTexture64 = window.loadTexture("res/png/Obstacle64_light.png");
SDL_Texture* bgTexture = window.loadTexture("res/png/bg.png");
SDL_Texture* powerMeterTexture_FG = window.loadTexture("res/png/powermeter_fg.png");
SDL_Texture* powerMeterTexture_BG = window.loadTexture("res/png/powermeter_bg.png");
SDL_Texture* powerMeterTexture_overlay = window.loadTexture("res/png/powermeter_overlay.png");



SDL_Color white = { 255, 255, 255 };
SDL_Color black = { 0, 0, 0 };
TTF_Font* font32 = TTF_OpenFont("res/font/font.ttf", 32);
TTF_Font* font48 = TTF_OpenFont("res/font/font.ttf", 48);
TTF_Font* font24 = TTF_OpenFont("res/font/font.ttf", 24);

Ball balls[2] = {Ball(Pos(0, 0), ballTexture, pointTexture, powerMeterTexture_FG, powerMeterTexture_BG, 0), Ball(Pos(0, 0), ballTexture, pointTexture, powerMeterTexture_FG, powerMeterTexture_BG, 1)};
std::vector<Hole> holes = {Hole(Pos(0, 0), holeTexture), Hole(Pos(0, 0), holeTexture)};

std::vector<Obstacle> loadObstacles(int level)
{
	std::vector<Obstacle> temp = {};

	/* midifcation for the obstacles based on the current level */
	switch(level) 
	{
		case 0:
			temp.push_back(Obstacle(Pos(64*3, 64*3), ObstacleLightTexture64));
			temp.push_back(Obstacle(Pos(64*4, 64*3), ObstacleLightTexture64));

			temp.push_back(Obstacle(Pos(64*0, 64*3), ObstacleLightTexture64));
			temp.push_back(Obstacle(Pos(64*1, 64*3), ObstacleLightTexture64));

			temp.push_back(Obstacle(Pos(64*3 + 64*5, 64*3), ObstacleLightTexture64));
			temp.push_back(Obstacle(Pos(64*4 + 64*5, 64*3), ObstacleLightTexture64));

			temp.push_back(Obstacle(Pos(64*0 + 64*5, 64*3), ObstacleLightTexture64));
			temp.push_back(Obstacle(Pos(64*1 + 64*5, 64*3), ObstacleLightTexture64));
		break;
		case 1:
			temp.push_back(Obstacle(Pos(64*2, 64*3), ObstacleLightTexture64));

			temp.push_back(Obstacle(Pos(64*4 + 64*5, 64*3), ObstacleLightTexture64));
		break;
	}
	return temp;
}

int level = 0;
std::vector<Obstacle> Obstacles = loadObstacles(level);

bool gameRunning = true ;
bool mouseDown = false;
bool mousePressed = false;

bool swingPlayed = false;
bool secondSwingPlayed = false;


SDL_Event event;

State gameState = G_TITLE; //0 = title screen, 1 = game, 2 = end screen

Uint64 currentTick = SDL_GetPerformanceCounter();
Uint64 lastTick = 0;
double deltaTime = 0 ;

void loadLevel(int level)
{
	if (level > 2)
	{
		gameState = G_END;
		return;
	}
	balls[0].setVelocity(0, 0);
	balls[1].setVelocity(0,0);
    balls[0].setScale(1, 1);
	balls[1].setScale(1, 1);
	balls[0].setWin(false);
	balls[1].setWin(false);

	Obstacles = loadObstacles(level);

	switch (level)
	{
		case 0:
			balls[0].setPos(24 + 32*4, 24 + 32*11);
			balls[1].setPos(24 + 32*4 + 32*10, 24 + 32*11);

			holes.at(0).setPos(24 + 32*4, 22 + 32*2);
			holes.at(1).setPos(24 + 32*4 + 32*10, 22 + 32*2);
		break;
		case 1:
			balls[0].setPos(24 + 32*4, 24 + 32*11);
			balls[1].setPos(24 + 32*4 + 32*10, 24 + 32*11);

			holes.at(0).setPos(24 + 32*4, 22 + 32*2);
			holes.at(1).setPos(24 + 32*4 + 32*10, 22 + 32*2);
		break;
	}
}



void  update ()
{
	
	lastTick = currentTick;
	currentTick = SDL_GetPerformanceCounter();
	deltaTime = (double)((currentTick - lastTick)*1000 / (double)SDL_GetPerformanceFrequency() );

	mousePressed = false;
	//Get our controls and events
	while (SDL_PollEvent(&event))
	{
		switch(event.type)
		{
		case SDL_QUIT:
			gameRunning = false ;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				mouseDown = true;
				mousePressed = true;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				mouseDown = false;
			}
			break;
		}
	}

	if (gameState == G_GAME)
	{
		for (Ball& b : balls)
		{
			/* updating the state of the tow balls */
			b.update(deltaTime, mouseDown, mousePressed, Obstacles, holes);
		}
		/* if both balls hit the hole then increase the level up. */
		if (balls[0].getScale().x < -1 && balls[1].getScale().x < -1)
 		{
        	level++;
			loadLevel(level);
    	}
	}
}

void graphics()
{
	window.clear();
	window.render(0, 0, bgTexture);
	for (Hole& h : holes)
	{
		window.render(h);
	}
	for (Ball& b : balls)
	{
		for (Obj& e : b.getPoints())
		{
			window.render(e);
		}
		window.render(b);
	}
	for (Obstacle& t : Obstacles)
	{ 
		window.render(t);
	}
	for (Ball& b : balls)
	{
		for (Obj& e : b.getPowerBar())
		{
			window.render(e);
		}
		window.render(b.getPowerBar().at(0).getPos().x, b.getPowerBar().at(0).getPos().y, powerMeterTexture_overlay);
		
	}
	if (gameState == G_END)
	{
		window.renderCenter(0, -32, "THE END", font48, white);
	}
	window.display();
}

void titleScreen()
{
	if (SDL_GetTicks() < 2000)
	{
		//Get our controls and events
		while (SDL_PollEvent(&event))
		{
			switch(event.type)
			{
			case SDL_QUIT:
				gameRunning = false ;
				break;
			}
		}

		window.clear();
		window.render(0, 0, bgTexture);
		window.renderCenter(0, 0, "Golf", font32, white);
		window.display();
	}
	else
	{
		lastTick = currentTick;
		currentTick = SDL_GetPerformanceCounter();
		deltaTime = (double)((currentTick - lastTick)*1000 / (double)SDL_GetPerformanceFrequency() );

		//Get our controls and events
		while (SDL_PollEvent(&event))
		{
			switch(event.type)
			{
			case SDL_QUIT:
				gameRunning = false ;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT)
				{

					gameState = G_GAME;
				}
				break;
			}
		}
		window.clear();
		window.render(0, 0, bgTexture);
		window.renderCenter(0, 240 - 48 - 16*5, "START", font32, white);
		window.display();
	}
}
void  game ()
{
	if (gameState == 0)
	{
		titleScreen();
	}
	else
	{
		update();
		graphics();
	}
}
int main(int argc, char* args[])
{
	loadLevel(level);
	while (gameRunning)
	{
		game();
	}

	window.cleanUp();
	TTF_CloseFont(font32);
	TTF_CloseFont(font24);
	SDL_Quit();
	TTF_Quit();
	return 0;
}