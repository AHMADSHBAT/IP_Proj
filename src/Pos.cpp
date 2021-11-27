#include <Pos.hpp>
#include <iostream>



Pos::Pos()
    :X(0.0f), Y(0.0f){}


Pos::Pos(float x, float y)
    :X(x), Y(y){}

void Pos::PosPrint()
{
    std::cout << "ball at position " << X << " and " << Y  << " \n";
}

Pos::~Pos(){}

