#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <MainWin.hpp>
#include <SDL_ttf.h>


MainWin::MainWin(const char* p_title, int p_w, int p_h)
	:window(NULL), renderer(NULL)
{
	window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h, SDL_WINDOW_SHOWN);

	if (window == NULL)
	{
		std::cout << "Window failed to init. Error: " << SDL_GetError() << std::endl;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* MainWin::loadTexture(const char* p_filePath)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(renderer, p_filePath);

	if (texture == NULL)
		std::cout << "Failed to load texture. Error: " << SDL_GetError() << std::endl;

	return texture;
}

void MainWin::cleanUp()
{
	SDL_DestroyWindow(window);
}

void MainWin::clear()
{
	SDL_RenderClear(renderer);
}

void MainWin::render(Obj& p_Obj)
{
	SDL_Rect src; 
	src.x = p_Obj.getCurrentFrame().x;
	src.y = p_Obj.getCurrentFrame().y;
	src.w = p_Obj.getCurrentFrame().w;
	src.h = p_Obj.getCurrentFrame().h;

	SDL_Rect dst;
	dst.x = p_Obj.getPos().X + (p_Obj.getCurrentFrame().w - p_Obj.getCurrentFrame().w*p_Obj.getScale().X)/2;
	dst.y = p_Obj.getPos().Y + (p_Obj.getCurrentFrame().h - p_Obj.getCurrentFrame().h*p_Obj.getScale().Y)/2;
	dst.w = p_Obj.getCurrentFrame().w*p_Obj.getScale().X;
	dst.h = p_Obj.getCurrentFrame().h*p_Obj.getScale().Y;

	SDL_RenderCopyEx(renderer, p_Obj.getTex(), &src, &dst, p_Obj.getAngle(), 0, SDL_FLIP_NONE);
}

void MainWin::render(int x, int y, SDL_Texture* p_tex)
{
	SDL_Rect src; 
	src.x = 0;
	src.y = 0;
	src.w;
	src.h;

	SDL_QueryTexture(p_tex, NULL, NULL, &src.w, &src.h);

	SDL_Rect dst;
	dst.x = x;
	dst.y = y;
	dst.w = src.w;
	dst.h = src.h;

	SDL_RenderCopy(renderer, p_tex, &src, &dst);
}

void MainWin::render(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor)
{
		SDL_Surface* surfaceMessage = TTF_RenderText_Blended( font, p_text, textColor);
		SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

		SDL_Rect src;
		src.x = 0;
		src.y = 0;
		src.w = surfaceMessage->w;
		src.h = surfaceMessage->h; 

		SDL_Rect dst;
		dst.x = p_x;
		dst.y = p_y;
		dst.w = src.w;
		dst.h = src.h;

		SDL_RenderCopy(renderer, message, &src, &dst);
		SDL_FreeSurface(surfaceMessage);
	 	SDL_DestroyTexture(message);
}

void MainWin::renderCenter(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor)
{
		SDL_Surface* surfaceMessage = TTF_RenderText_Blended( font, p_text, textColor);
		SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

		SDL_Rect src;
		src.x = 0;
		src.y = 0;
		src.w = surfaceMessage->w;
		src.h = surfaceMessage->h; 

		SDL_Rect dst;
		dst.x = 640/2 - src.w/2 + p_x;
		dst.y = 480/2 - src.h/2 + p_y;
		dst.w = src.w;
		dst.h = src.h;

		SDL_RenderCopy(renderer, message, &src, &dst);
		SDL_FreeSurface(surfaceMessage);
		SDL_DestroyTexture(message);
}

void MainWin::display()
{
	SDL_RenderPresent(renderer);
}