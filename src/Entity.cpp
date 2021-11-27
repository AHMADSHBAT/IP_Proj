#include <Entity.hpp>
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>




Entity::Entity(Pos & p, SDL_Texture * tex, char * n)
    :pos(p), texture(tex), name(n)
{
    std::cout << "Entity " << name << " has been initialized" << std::endl;
}




