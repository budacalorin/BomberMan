#include "powerup.h"

#include <SFML/Graphics.hpp>
#include "init.h"

power_up::power_up()
{
    forma.setSize(sf::Vector2f(player_x,player_y));
    ptexture=new sf::Texture;

}

void power_up::set_color(sf::Color culoare)
{
    forma.setFillColor(culoare);
}

void power_up::set_position(int x,int y)
{
    forma.setPosition(sf::Vector2f(x,y));
}
