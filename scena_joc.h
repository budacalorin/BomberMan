#ifndef SCENA_JOC
#define SCENA_JOC

#include "perete.h"
#include "player.h"
#include "bomba.h"
#include "particula.h"
#include "powerup.h"

class scena_joc{
public:
    int numar_playeri;
    int numar_ziduri;
    int numar_bombe=0;
    int numar_particule=0;
    int timp_frame_precedent;
    int numar_power_ups;
    player playeri[6];
    perete pereti[400];
    bomba bombe[400];
    particula particule[10000];
    power_up power_ups[200];

    void update();

    void update_bombe();

    void miscare_playeri();

    void deplasare_playeri();

    void verificare_finish();

    void draw();

    void draw_pereti();

    void draw_playeri();

    void draw_bombe();

    void draw_explozii();

    void reset(int x);

    void adaugare_perete(int x,int y,int size_x,int size_y);

    void adaugare_player(player playeri[],int indice,int x,int y,sf::Color culoare,sf::Keyboard::Key sus,sf::Keyboard::Key jos,sf::Keyboard::Key stanga,sf::Keyboard::Key dreapta,sf::Keyboard::Key act);

    void update_timp();

    void update_particule();

    void draw_particule();

    void draw_power_ups();

    void update_power_ups();

    void afisare_statistici();




private:
    void init_pereti_1(perete pereti[],int &numar_pereti);

    void generare_pereti_random();

    void generare_power_ups_random();

    bool coliziune_bomba_bomba(int indice_curent,bomba bombe[],int numar_bombe);
};

#endif // SCENA_JOC
