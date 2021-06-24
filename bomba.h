#ifndef BOMBA
#define BOMBA

#include <SFML/Graphics.hpp>
#include "perete.h"
#include "player.h"
#include "particula.h"

class bomba {
public:
    sf::RectangleShape forma;
    int dimensiune_explozie;
    float countdown;
    int activ=0;
    sf::Texture *ptexture;
    player *proprietar;

    bomba();

    ~bomba();

    void set_position(int x,int y);

    void set_dimensiune_explozie(int x);

    void explodare(perete pereti[],player playeri[],int numar_pereti,int numar_playeri,bomba bombe[],int numar_bombe,particula particule[],int &numar_particule);

    void explozie(int numar_particule_explozie,int x,int y,sf::RectangleShape border,particula particule[],int &numar_particule);
private:
    bool verificare_explozie(int x_nou,int y_nou,perete pereti[],player playeri[],int numar_pereti,int numar_playeri,bomba bombe[],int numar_bombe,particula particule[],int &numar_particule,int p[]);
};


#endif // BOMBA
