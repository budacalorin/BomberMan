#include "player.h"
#include "init.h"
#include <iostream>

bool coliziune_player(sf::RectangleShape forma,perete pereti[],int numar_pereti);
void adaugare_particula(int x,int y,float viteza_x,float viteza_y,int unghi,int countdown,sf::RectangleShape border,particula particule[],int &numar_particule);


using namespace std;

player::player()
{
    forma.setSize(sf::Vector2f(player_x,player_y));
    numar_bombe=bombe_ramase=2;
    timp_detonare_bomba=2500000;
    dimensiune_explozie=2;
    forma.setTexture(texture_dreapta);
}

void player::deplasare()
{
    if (inghetat>0)
    {
        if (!up&&directie!=3)
            up=sf::Keyboard::isKeyPressed(sus);

        if (!down&&directie!=1)
            down=sf::Keyboard::isKeyPressed(jos);

        if (!left&&directie!=2)
            left=sf::Keyboard::isKeyPressed(stanga);

        if (!right&&directie!=4)
            right=sf::Keyboard::isKeyPressed(dreapta);

        actiune=sf::Keyboard::isKeyPressed(action);
    }
}

void player::miscare(player playeri[],perete pereti[],int numar_playeri,int numar_pereti)
{
    if (inghetat>0)
    {
        if (up)
        {
            forma.setPosition(sf::Vector2f(forma.getPosition().x,forma.getPosition().y-pixel_per_frame));
            if (coliziune_player(forma,pereti,numar_pereti)==1)
                forma.setPosition(sf::Vector2f(forma.getPosition().x,forma.getPosition().y+pixel_per_frame));
            up=0;
        }//else
        if (down)
        {
            forma.setPosition(sf::Vector2f(forma.getPosition().x,forma.getPosition().y+pixel_per_frame));
            if (coliziune_player(forma,pereti,numar_pereti))
                forma.setPosition(sf::Vector2f(forma.getPosition().x,forma.getPosition().y-pixel_per_frame));
            down=0;

        }//else
        if (right)
        {
            forma.setTexture(texture_dreapta);
            forma.setPosition(sf::Vector2f(forma.getPosition().x+pixel_per_frame,forma.getPosition().y));
            if (coliziune_player(forma,pereti,numar_pereti))
                forma.setPosition(sf::Vector2f(forma.getPosition().x-pixel_per_frame,forma.getPosition().y));
            right=0;
        }//else
        if (left)
        {
            forma.setTexture(texture_stanga);
            forma.setPosition(sf::Vector2f(forma.getPosition().x-pixel_per_frame,forma.getPosition().y));
            if (coliziune_player(forma,pereti,numar_pereti))
                forma.setPosition(sf::Vector2f(forma.getPosition().x+pixel_per_frame,forma.getPosition().y));
            left=0;
        }
        if (actiune)
        {

        }
    }
}
void player::setTaste(sf::Keyboard::Key su,sf::Keyboard::Key jo,sf::Keyboard::Key st,sf::Keyboard::Key dr,sf::Keyboard::Key act)
{
    action=act;
    sus=su;
    jos=jo;
    stanga=st;
    dreapta=dr;
}

