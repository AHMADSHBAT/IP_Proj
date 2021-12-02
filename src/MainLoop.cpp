#include <MainLoop.hpp>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <MainWin.hpp>
#include <Ball.hpp>
#include <memory>


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
    SDL_Texture * backGround = mainwin->loadTexture("res/png/1.png", 0);
    Ball * ball = new Ball(Pos(0.0f, 0.0f), 0);





    int state = 0;
    SDL_Event event;
    bool to_quit = true;
    while(to_quit)
    {
        switch(SDL_WaitEvent(&event))
        {
            case SDL_QUIT:
                to_quit = false;
                break;

            case SDL_MOUSEBUTTONDOWN:
                if(event.button.button == SDL_BUTTON_LEFT)
                {
                    std::unique_ptr<Pos> mouseClicked = std::make_unique<Pos>(event.button.x, event.button.y);
                    std::unique_ptr<Pos> mouseReleased = std::make_unique<Pos>(event.button.x, event.button.y);
                    state = 1;
                    while(event.button.button == SDL_PRESSED)
                    {
                        mouseReleased->X = event.button.x;
                        mouseReleased->Y = event.button.y;
                    }
                    

                    
                }

        mainwin->rendererClear();
        mainwin->render(backGround);
        mainwin->display();
        }
        
    }

}

