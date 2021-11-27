#include <MainLoop.hpp>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <MainWin.hpp>


void MainLoop::run()
{

if(SDL_Init(SDL_INIT_VIDEO) > 0)
   {
       std::cout << "we have an error with the initiolization\n";
       return;
   }

   if(!(IMG_Init(IMG_INIT_PNG)))
   {
       std::cout << "error with the IMG init\n";
       return;
   }

/*    loading........   */
MainWin * mainwin = new MainWin("hello", 1000, 1000);
SDL_Texture * backGround = mainwin->LoadTexture("res/png/1.png", 0);





SDL_Event event;
bool to_quit = true;
while(to_quit)
{
    while(SDL_WaitEvent(&event))
    {
        if(event.type == SDL_QUIT)
            to_quit = false;
    mainwin->rendererClear();
    mainwin->render(backGround);
    mainwin->display();
    }
    
}

}