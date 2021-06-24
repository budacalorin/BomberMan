#include "particula.h"
#include <cmath>
#include <iostream>
particula::particula()
{
    forma.setSize(sf::Vector2f(2,2));
    forma.setFillColor(sf::Color::Red);
}

void particula::setup(int x,int y,float viteza_Y,float viteza_X,int UNGHI, int COUNTDOWN,sf::RectangleShape BORDER)
{
    viteza_x=viteza_X;
    viteza_y=viteza_Y;
    unghi=UNGHI;
    countdown=COUNTDOWN;
    border=BORDER;
    forma.setPosition(sf::Vector2f(x,y));
}

void particula::miscare()
{
    if (countdown)
    {
        float sin_unghi=-sin(unghi*3.14/180);
        float cos_unghi=cos(unghi*3.14/180);
        //std::cout << sin_unghi<< " " << cos_unghi <<std::endl;
        forma.move(sf::Vector2f(cos_unghi*viteza_x,sin_unghi*viteza_y));
    }
}

void particula::test_colizune()
{
    if (forma.getGlobalBounds().intersects(border.getGlobalBounds())==0)
    {
        viteza_x=viteza_y=0;
    }
}
