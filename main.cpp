#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "init.h"
//#include "scena_meniu.h"
//#include "scena_joc.h"
//#include "player.h"
using namespace std;

/////////////////////////////////////////////////////////////

int latime_pereti_exterior=30;
int hight=510+latime_pereti_exterior*2;
int width=510+latime_pereti_exterior*2;
int game_on=1;
int player_x=30;
int player_y=30;
int pixel_per_frame=1;
int bomba_x=30;
int bomba_y=30;
sf::Texture *pt_inima;
sf::Texture *pt_bomba;
sf::Texture *pt_shoe;
sf::Texture *pt_foc;
sf::Texture t_inima;
sf::Texture t_bomba;
sf::Texture t_shoe;
sf::Texture t_foc;
sf::Texture harta;
sf::Sprite sprite_harta;
sf::Texture zid_solid;
sf::Texture *pzid_solid;
sf::Texture zid_fragil;
sf::Texture *pzid_fragil;
sf::Texture *p_player1_dreapta;
sf::Texture player1_dreapta;
sf::Texture *p_player1_stanga;
sf::Texture player1_stanga;
sf::Texture *p_player2_dreapta;
sf::Texture player2_dreapta;
sf::Texture *p_player2_stanga;
sf::Texture player2_stanga;
sf::Texture *p_player3_dreapta;
sf::Texture player3_dreapta;
sf::Texture *p_player3_stanga;
sf::Texture player3_stanga;
sf::Texture *p_player4_dreapta;
sf::Texture player4_dreapta;
sf::Texture *p_player4_stanga;
sf::Texture player4_stanga;
sf::Texture *pt0,*pt1,*pt2,*pt3,*pt4,*pt5,*pt6,*pt7,*pt8,*pt9;
sf::Texture t0,t1,t2,t3,t4,t5,t6,t7,t8,t9;

/////////////////////////////////////////////////////////////

sf::Clock ceas;
sf::RenderWindow window(sf::VideoMode(1366,768),"BOMBER MAN",sf::Style::Fullscreen);
scena_meniu meniu_principal;
scena_joc joc_principal;

int scena_curenta=1;


int main()
{
    meniu_principal.adaugare_optiune("PLAY");
    meniu_principal.adaugare_optiune("EXIT");

    t_bomba.loadFromFile("img/power_up_bomba.png");
    t_foc.loadFromFile("img/power_up_foc.png");
    t_shoe.loadFromFile("img/power_up_shoe.png");
    t_inima.loadFromFile("img/power_up_inima.png");

    harta.loadFromFile("img/atempt2.png");
    sprite_harta.setTexture(harta);
    //sprite_harta.setPosition(sf::Vector2f(latime_pereti_exterior,latime_pereti_exterior));

    zid_solid.loadFromFile("img/zid_solid_3.png");
    pzid_solid=&zid_solid;

    zid_fragil.loadFromFile("img/zid_fragil.png");
    pzid_fragil=&zid_fragil;

    player1_dreapta.loadFromFile("img/player1_dreapta.png");
    p_player1_dreapta=&player1_dreapta;

    player1_stanga.loadFromFile("img/player1_stanga.png");
    p_player1_stanga=&player1_stanga;

    player2_dreapta.loadFromFile("img/player2_dreapta.png");
    p_player2_dreapta=&player2_dreapta;

    player2_stanga.loadFromFile("img/player2_stanga.png");
    p_player2_stanga=&player2_stanga;

    player3_dreapta.loadFromFile("img/player3_dreapta.png");
    p_player3_dreapta=&player3_dreapta;

    player3_stanga.loadFromFile("img/player3_stanga.png");
    p_player3_stanga=&player3_stanga;

    player4_dreapta.loadFromFile("img/player4_dreapta.png");
    p_player4_dreapta=&player4_dreapta;

    player4_stanga.loadFromFile("img/player4_stanga.png");
    p_player4_stanga=&player4_stanga;

    t0.loadFromFile("img/0.png");
    pt0=&t0;
    t1.loadFromFile("img/1.png");
    pt1=&t1;
    t2.loadFromFile("img/2.png");
    pt2=&t2;
    t3.loadFromFile("img/3.png");
    pt3=&t3;
    t4.loadFromFile("img/4.png");
    pt4=&t4;
    t5.loadFromFile("img/5.png");
    pt5=&t5;
    t6.loadFromFile("img/6.png");
    pt6=&t6;
    t7.loadFromFile("img/7.png");
    pt7=&t7;
    t8.loadFromFile("img/8.png");
    pt8=&t8;
    t9.loadFromFile("img/9.png");
    pt9=&t9;



    pt_bomba=&t_bomba;
    pt_foc=&t_foc;
    pt_shoe=&t_shoe;
    pt_inima=&t_inima;

    //ceas.restart();
    //sf::Clock clock;
    //clock.restart();
   // int timp;
    //int timp_per_frame;
    //timp_per_frame=100000/6;
    while (game_on==1)
    {
        //timp=clock.getElapsedTime().asMicroseconds();
        if (scena_curenta==1)
            meniu_principal.update();
        if (scena_curenta==2)
        {
            joc_principal.update();
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type==sf::Event::Closed)
                    game_on=0;
            }
        }
        //if (clock.getElapsedTime().asMicroseconds()-timp<timp_per_frame)
          //  sf::sleep(sf::microseconds(timp_per_frame-(clock.getElapsedTime().asMicroseconds()-timp)));
        //clock.restart();
    }

    return 0;
}
