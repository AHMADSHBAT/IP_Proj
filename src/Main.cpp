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

bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "HEY.. SDL_Init HAS FAILED. SDL_ERROR: " << SDL_GetError() << std::endl;
	if (!(IMG_Init(IMG_INIT_PNG)))
		std::cout << "IMG_init has failed. Error: " << SDL_GetError() << std::endl;
	if (!(TTF_Init()))
		std::cout << "TTF_init has failed. Error: " << SDL_GetError() << std::endl;
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	return true;
}

bool SDLinit = init();

MainWin window("Twini-Golf", 640, 480);

SDL_Texture* ballTexture = window.loadTexture("res/gfx/ball.png");
SDL_Texture* holeTexture = window.loadTexture("res/gfx/hole.png");
SDL_Texture* pointTexture = window.loadTexture("res/gfx/point.png");
SDL_Texture* ObstacleDarkTexture32 = window.loadTexture("res/gfx/Obstacle32_dark.png");
SDL_Texture* ObstacleDarkTexture64 = window.loadTexture("res/gfx/Obstacle64_dark.png");
SDL_Texture* ObstacleLightTexture32 = window.loadTexture("res/gfx/Obstacle32_light.png");
SDL_Texture* ObstacleLightTexture64 = window.loadTexture("res/gfx/Obstacle64_light.png");
SDL_Texture* ballShadowTexture = window.loadTexture("res/gfx/ball_shadow.png");
SDL_Texture* bgTexture = window.loadTexture("res/gfx/bg.png");
SDL_Texture* uiBgTexture = window.loadTexture("res/gfx/UI_bg.png");
SDL_Texture* levelTextBgTexture = window.loadTexture("res/gfx/levelText_bg.png");
SDL_Texture* powerMeterTexture_FG = window.loadTexture("res/gfx/powermeter_fg.png");
SDL_Texture* powerMeterTexture_BG = window.loadTexture("res/gfx/powermeter_bg.png");
SDL_Texture* powerMeterTexture_overlay = window.loadTexture("res/gfx/powermeter_overlay.png");
SDL_Texture* logoTexture = window.loadTexture("res/gfx/logo.png");
SDL_Texture* click2start = window.loadTexture("res/gfx/click2start.png");
SDL_Texture* endscreenOverlayTexture = window.loadTexture("res/gfx/end.png");
SDL_Texture* splashBgTexture = window.loadTexture("res/gfx/splashbg.png");

// Mix_Chunk* chargeSfx = Mix_LoadWAV("res/sfx/charge.mp3");
// Mix_Chunk* swingSfx = Mix_LoadWAV("res/sfx/swing.mp3");
// Mix_Chunk* holeSfx = Mix_LoadWAV("res/sfx/hole.mp3");


SDL_Color white = { 255, 255, 255 };
SDL_Color black = { 0, 0, 0 };
// TTF_Font* font32 = TTF_OpenFont("res/font/font.ttf", 32);
// TTF_Font* font48 = TTF_OpenFont("res/font/font.ttf", 48);
// TTF_Font* font24 = TTF_OpenFont("res/font/font.ttf", 24);

Ball ball(Pos(0, 0), ballTexture, pointTexture, powerMeterTexture_BG, 0);
Hole hole(Pos(0, 0), holeTexture);

std::vector<Obstacle> loadObstacles()
{
    std::vector<Obstacle> vec;
    vec.push_back(Obstacle(Pos(64 * 3, 64 * 3), ObstacleDarkTexture64));
    vec.push_back(Obstacle(Pos(64 * 4, 64 * 3), ObstacleDarkTexture64));

    vec.push_back(Obstacle(Pos(64 * 0, 64 * 3), ObstacleDarkTexture64));
    vec.push_back(Obstacle(Pos(64 * 1, 64 * 3), ObstacleDarkTexture64));

    vec.push_back(Obstacle(Pos(64 * 3 + 64 * 5, 64 * 3), ObstacleLightTexture64));
    vec.push_back(Obstacle(Pos(64 * 4 + 64 * 5, 64 * 3), ObstacleLightTexture64));

    vec.push_back(Obstacle(Pos(64 * 0 + 64 * 5, 64 * 3), ObstacleLightTexture64));
    vec.push_back(Obstacle(Pos(64 * 1 + 64 * 5, 64 * 3), ObstacleLightTexture64));
		
	return vec;
}

std::vector<Obstacle> obstacles = loadObstacles();

bool gameRunning = true;
bool mouseDown = false;
bool mousePressed = false;

bool swingPlayed = false;
bool secondSwingPlayed = false;


SDL_Event event;

int state = 0; //0 = title screen, 1 = game, 2 = end screen

Uint64 currentTick = SDL_GetPerformanceCounter();
Uint64 lastTick = 0;
double deltaTime = 0;

void loadLevel(int level)
{
	if (level > 4)
	{
		state = 2;
		return;
	}
	ball.setVelocity(0, 0);
	ball.setVelocity(0,0);
    ball.setScale(1, 1);
	ball.setScale(1, 1);
	ball.setWin(false);
	ball.setWin(false);

	obstacles = loadObstacles();

	
    ball.setPos(24 + 32*4, 24 + 32*11);
    ball.setPos(24 + 32*4 + 32*10, 24 + 32*11);

			
}

const char* getStrokeText()
{
	int biggestStroke = 0;
	if (ball.strokes > ball.strokes)
	{
		biggestStroke = ball.strokes;
	}
	else
	{
		biggestStroke = ball.strokes;
	}
	std::string s = std::to_string(biggestStroke);
	s = "STROKES: " + s;
	return s.c_str();
}


void update()
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
			gameRunning = false;
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

}

void graphics()
{
	window.clear();
	window.render(0, 0, bgTexture);
	window.render(hole);
	for (Obstacle& t : obstacles)
	{ 
		window.render(t);
	}
	
	window.render(ball.powerBar);
		
	window.render(ball.powerBar.getPos().X, ball.powerBar.getPos().Y, powerMeterTexture_overlay);
	window.display();
}

void titleScreen()
{
    while (SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_QUIT:
            gameRunning = false;
            break;
        }
    }

    window.clear();
    window.render(0, 0, bgTexture);
    window.render(0, 0, splashBgTexture);
    window.display();

}
void game()
{
	if (state == 0)
	{
		titleScreen();
	}
	else
	{
		update();
		graphics();
	}
}

