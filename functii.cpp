#include <SFML/Graphics.hpp>
#include "perete.h"
#include "particula.h"
#include "player.h"
#include "bomba.h"
#include <iostream>

bool coliziune_player(sf::RectangleShape forma,perete pereti[],int numar_pereti)
{
    for (int i=1;i<=numar_pereti;i++)
    if (forma.getGlobalBounds().intersects(pereti[i].forma.getGlobalBounds()))
        return 1;
    return 0;
}
void adaugare_particula(int x,int y,float viteza_x,float viteza_y,int unghi,int countdown,sf::RectangleShape border,particula particule[],int &numar_particule)
{
    //std::cout <<numar_particule <<std::endl;
    for (int i=1;i<=numar_particule;i++)
    {

        if (particule[i].viteza_x==0&&particule[i].viteza_y==0)
        {
            //std::cout << "da\n\n\n\n\n";
            particule[i].setup(x,y,viteza_x,viteza_y,unghi,countdown,border);
            return;
        }
    }
    //std::cout << "dA\n";
    particule[++numar_particule].setup(x,y,viteza_x,viteza_y,unghi,countdown,border);
}

int coliziune_player_bomba(player playerul,bomba bombe[],int numar_bombe)
{
    for (int i=numar_bombe;i>=1;i--)
    {
        if (playerul.forma.getGlobalBounds().intersects(bombe[i].forma.getGlobalBounds())&&bombe[i].activ==1)
        {
            return i;
        }
    }
    return 0;
}

void restart_playeri(player playeri[],int numar_playeri)
{
    for (int i=0;i<5;i++)
    {
        playeri[i].bombe_ramase=2;
        playeri[i].dimensiune_explozie=2;
        playeri[i].powerup_cooldown_bombe=0;
        playeri[i].powerup_miscare=0;
    }
}
