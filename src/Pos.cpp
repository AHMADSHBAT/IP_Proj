#include <Pos.hpp>
#include <iostream>



Pos::Pos()
    :x(0.0f), y(0.0f){}


Pos::Pos(float x, float y)
    :x(x), y(y){}

void Pos::PosPrint()
{
    std::cout << "ball at position " << x << " and " << y  << " \n";
}

Pos::~Pos(){}

