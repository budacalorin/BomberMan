#ifndef POWER_UP
#define POWER_UP

#include <SFML/Graphics.hpp>

class power_up{
public:
    int tip;
    sf::RectangleShape forma;
    int efect_numar_bombe;
    int efect_viteza;
    int efect_vieti;
    int efect_cooldown_bombe;
    int efect_raza;
    sf::Texture *ptexture;

    bool activ=0;

    power_up();

    void set_color(sf::Color culoare);

    void set_position(int x,int y);

};



#endif // POWER_UP
