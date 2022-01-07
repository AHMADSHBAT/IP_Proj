#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <utility>
#include <SDL_ttf.h>
#include <Obj.hpp>

typedef SDL_Texture* TexPtr;


class MainWin 
{
public:
	MainWin(const char* p_title, int p_w, int p_h);
	SDL_Texture* loadTexture(const char* p_filePath);
	void cleanUp();
	void clear();
	void render(Obj& p_Obj);
	void render(int x, int y, SDL_Texture* p_tex);
	void render(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor);
	void renderCenter(float p_x, float p_y, const char* p_text, TTF_Font* font, SDL_Color textColor);
	void display();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};