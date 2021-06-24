#ifndef INIT
#define INIT

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "scena_meniu.h"
#include "scena_joc.h"


extern int hight;
extern int width;
extern int latime_pereti_exterior;
extern sf::RenderWindow window;
extern int game_on;
extern int player_x;
extern int player_y;
extern int pixel_per_frame;
extern int bomba_x;
extern int bomba_y;
extern int scena_curenta;
extern scena_meniu meniu_principal;
extern scena_joc joc_principal;
extern sf::Clock ceas;
extern sf::Texture *pt_inima;
extern sf::Texture *pt_bomba;
extern sf::Texture *pt_shoe;
extern sf::Texture *pt_foc;
extern sf::Texture harta;
extern sf::Sprite sprite_harta;
extern sf::Texture *pzid_solid;
extern sf::Texture *pzid_fragil;
extern sf::Texture *p_player1_dreapta;
extern sf::Texture *p_player1_stanga;
extern sf::Texture *p_player2_dreapta;
extern sf::Texture *p_player2_stanga;
extern sf::Texture *p_player3_dreapta;
extern sf::Texture *p_player3_stanga;
extern sf::Texture *p_player4_dreapta;
extern sf::Texture *p_player4_stanga;
extern sf::Texture player1_dreapta;
extern sf::Texture player1_stanga;
extern sf::Texture player2_dreapta;
extern sf::Texture player2_stanga;
extern sf::Texture player3_dreapta;
extern sf::Texture player3_stanga;
extern sf::Texture player4_dreapta;
extern sf::Texture player4_stanga;


extern sf::Texture *pt0,*pt1,*pt2,*pt3,*pt4,*pt5,*pt6,*pt7,*pt8,*pt9;





#endif // INIT
