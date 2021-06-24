#ifndef PLAYER
#define PLAYER

#include <SFML/Graphics.hpp>
#include "perete.h"
//#include "bomba.h"

using namespace std;


class player
{
public:
    sf::RectangleShape forma;
    int up=0,down=0,left=0,right=0,directie=0,actiune=0;
    sf::Color culoare;
    int inghetat=1;
    bool cel_care_prinde;
    int indice_player;
    sf::Keyboard::Key sus,jos,stanga,dreapta,action;
    float cooldown_bombe=0;
    float cooldown_miscare=0;
    float powerup_miscare=0;
    float timp_detonare_bomba;
    int numar_bombe;
    int bombe_ramase;
    int dimensiune_explozie;
    int powerup_cooldown_bombe;
    sf::Texture *texture_dreapta,*texture_stanga;

public:
    player();
    void setPosition (int x,int y)
    {
        forma.setPosition(sf::Vector2f(x,y));
    }
    void setColor (sf::Color culoare_data)
    {
        forma.setFillColor(culoare_data);
        culoare=culoare_data;
    }
    void setStatut (bool e_cel_care_prinde)
    {
        cel_care_prinde=e_cel_care_prinde;
    }
    void setTaste (sf::Keyboard::Key su,sf::Keyboard::Key jo,sf::Keyboard::Key st,sf::Keyboard::Key dr,sf::Keyboard::Key act);
    void deplasare();
    void miscare(player playeri[],perete pereti_interior[],int numar_playeri,int numar_pereti);
};

#endif
