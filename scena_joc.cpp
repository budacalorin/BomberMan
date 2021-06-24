#include "scena_joc.h"
#include "init.h"
#include <iostream>
#include <cmath>
#include <time.h>
#include <cstdlib>

int coliziune_player_bomba(player playerul,bomba bombe[],int numar_bombe);
void restart_playeri(player playeri[],int numar_playeri);


void scena_joc::update()
{
    //if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
    //std::cout << numar_particule << std::endl << std::endl;
    update_particule();
    update_bombe();
    update_power_ups();
    update_timp();
    miscare_playeri();
    deplasare_playeri();
    draw();
    verificare_finish();
}

void scena_joc::draw()
{
    window.clear();
    window.draw(sprite_harta);

    draw_power_ups();
    draw_pereti();
    draw_bombe();
    draw_playeri();
    draw_particule();
    afisare_statistici();

    window.display();
}

void scena_joc::update_bombe()
{
    for (int i=1; i<=numar_bombe; i++)
    {
        if (bombe[i].activ==1&&bombe[i].countdown==0)
        {
            bombe[i].activ=0;
            bombe[i].explodare(pereti,playeri,numar_ziduri,numar_playeri,bombe,numar_bombe,particule,numar_particule);
        }
    }
}

void scena_joc::miscare_playeri()
{
    for (int i=1; i<=numar_playeri; i++)
    {
        if (playeri[i].cooldown_miscare==0)
        {
            int b1=0,b2=0;
            for (int j=1; j<=numar_bombe; j++)
            {
                if (playeri[i].forma.getGlobalBounds().intersects(bombe[j].forma.getGlobalBounds())&&bombe[j].activ==1)
                {
                   if (b1)
                        b2=j;
                   else
                        b1=j;
                }
            }
            int x=playeri[i].forma.getPosition().x;
            int y=playeri[i].forma.getPosition().y;
            playeri[i].miscare(playeri,pereti,numar_playeri,numar_ziduri);
            int B1=0,B2=0;
            for (int j=1; j<=numar_bombe; j++)
            {
                if (playeri[i].forma.getGlobalBounds().intersects(bombe[j].forma.getGlobalBounds())&&bombe[j].activ==1)
                {
                   if (B1)
                        B2=j;
                   else
                        B1=j;
                }
            }
            if (b1&&b2)
            {

                playeri[i].cooldown_miscare=5000-playeri[i].powerup_miscare*1000;
            }
            if (b1&&b2==0)
            {
                if (B1&&B2)
                {
                    playeri[i].forma.setPosition(sf::Vector2f(x,y));
                }
                else
                    playeri[i].cooldown_miscare=5000-playeri[i].powerup_miscare*1000;
            }
            if (b1==0)
                {if (B1==0)
                    playeri[i].cooldown_miscare=5000-playeri[i].powerup_miscare*1000;
                else
                    playeri[i].forma.setPosition(sf::Vector2f(x,y));

                }
        }


        if (playeri[i].actiune&&playeri[i].cooldown_bombe==0&&playeri[i].bombe_ramase!=0)
        {
            bombe[++numar_bombe].set_position((int)playeri[i].forma.getPosition().x/player_x*player_x,(int)playeri[i].forma.getPosition().y/player_y*player_y);
            if (playeri[i].forma.getPosition().x-bombe[numar_bombe].forma.getPosition().x>player_x/2)
                bombe[numar_bombe].forma.move(sf::Vector2f(player_x,0));
            if (playeri[i].forma.getPosition().y-bombe[numar_bombe].forma.getPosition().y>player_y/2)
                bombe[numar_bombe].forma.move(sf::Vector2f(0,player_y));
            bombe[numar_bombe].activ=1;
            if (coliziune_bomba_bomba(numar_bombe,bombe,numar_bombe))
            {
                bombe[numar_bombe].activ=0;
                numar_bombe--;

            }
            else
            {
                //playeri[i].cooldown_bombe=1000000-playeri[i].powerup_cooldown_bombe*200000;
                bombe[numar_bombe].set_dimensiune_explozie(playeri[i].dimensiune_explozie);
                playeri[i].actiune=0;
                playeri[i].bombe_ramase-=1;
                bombe[numar_bombe].countdown=2500000;
                bombe[numar_bombe].proprietar=&playeri[i];
            }
        }
    }
}

void scena_joc::deplasare_playeri()
{
    for (int i=1; i<=numar_playeri; i++)
    {
        playeri[i].deplasare();
    }
}

void scena_joc::verificare_finish()
{
    int nr=0;
    for (int i=1; i<=numar_playeri; i++)
    {
        if (playeri[i].inghetat<=0)
        {
        nr++;
        }

    }
    if (nr>=numar_playeri-1)
        {
            sf::Time timp;
            timp=sf::seconds(1);
            sf::sleep(timp);
            scena_curenta=1;
        }
}

void scena_joc::draw_pereti()
{
    for (int i=1; i<=numar_ziduri; i++)
        window.draw(pereti[i].forma);

}

void scena_joc::draw_playeri()
{
    for (int i=1; i<=numar_playeri; i++)
        if (playeri[i].inghetat>0)
            window.draw(playeri[i].forma);
}

void scena_joc::draw_bombe()
{
    for (int i=1; i<=numar_bombe; i++)
    {
        if (bombe[i].activ)
            window.draw(bombe[i].forma);
    }
}


void scena_joc::reset(int x)
{
    numar_playeri=x;
    for (int i=1;i<=numar_power_ups;i++)
    {
        power_ups[i].efect_cooldown_bombe=power_ups[i].efect_numar_bombe=power_ups[i].efect_raza=power_ups[i].efect_vieti=power_ups[i].efect_viteza=0;
    }
    numar_bombe=numar_ziduri=numar_particule=numar_power_ups=0;

    adaugare_player(playeri,1,latime_pereti_exterior,latime_pereti_exterior,sf::Color::Blue,sf::Keyboard::W,sf::Keyboard::S,sf::Keyboard::A,sf::Keyboard::D,sf::Keyboard::LControl);
    playeri[1].texture_dreapta=p_player1_dreapta;
    playeri[1].texture_stanga=p_player1_stanga;
    playeri[1].forma.setTexture(p_player1_dreapta);
    adaugare_player(playeri,2,width-latime_pereti_exterior-player_x,hight-latime_pereti_exterior-player_y,sf::Color::Yellow,sf::Keyboard::Up,sf::Keyboard::Down,sf::Keyboard::Left,sf::Keyboard::Right,sf::Keyboard::Enter);
    playeri[2].texture_dreapta=p_player2_dreapta;
    playeri[2].texture_stanga=p_player2_stanga;
    playeri[2].forma.setTexture(p_player2_stanga);
    if (x>2)
    {
        adaugare_player(playeri,3,player_x,hight-latime_pereti_exterior-player_y,sf::Color::Yellow,sf::Keyboard::I,sf::Keyboard::K,sf::Keyboard::J,sf::Keyboard::L,sf::Keyboard::Space);
        playeri[3].texture_dreapta=p_player3_dreapta;
        playeri[3].texture_stanga=p_player3_stanga;
        playeri[3].forma.setTexture(p_player3_dreapta);
    }
    if (x>3)
    {
        adaugare_player(playeri,4,width-player_x-latime_pereti_exterior,player_y,sf::Color::Yellow,sf::Keyboard::Numpad8,sf::Keyboard::Numpad5,sf::Keyboard::Numpad4,sf::Keyboard::Numpad6,sf::Keyboard::Numpad0);
        playeri[4].texture_dreapta=p_player4_dreapta;
        playeri[4].texture_stanga=p_player4_stanga;
        playeri[4].forma.setTexture(p_player4_dreapta);

    }
    adaugare_perete(0,0,width,latime_pereti_exterior);
    adaugare_perete(0,0,latime_pereti_exterior,hight);
    adaugare_perete(width-latime_pereti_exterior,0,latime_pereti_exterior,hight);
    adaugare_perete(0,hight-latime_pereti_exterior,width,latime_pereti_exterior);
    init_pereti_1(pereti,numar_ziduri);
    generare_pereti_random();
    generare_power_ups_random();
    restart_playeri(playeri,numar_playeri);
    timp_frame_precedent=ceas.getElapsedTime().asMicroseconds();
}

void scena_joc::adaugare_perete(int x,int y,int size_x,int size_y)
{
    pereti[++numar_ziduri].forma.setPosition(sf::Vector2f(x,y));
    pereti[numar_ziduri].forma.setSize(sf::Vector2f(size_x,size_y));
    pereti[numar_ziduri].forma.setFillColor(sf::Color::Transparent);
    pereti[numar_ziduri].poate_fi_explodat=0;
}

void scena_joc::adaugare_player(player playeri[],int indice,int x,int y,sf::Color culoare,sf::Keyboard::Key sus,sf::Keyboard::Key jos,sf::Keyboard::Key stanga,sf::Keyboard::Key dreapta,sf::Keyboard::Key act)
{

    playeri[indice].setPosition(x,y);
    //playeri[indice].setColor(culoare);
    playeri[indice].setTaste(sus,jos,stanga,dreapta,act);
    playeri[indice].inghetat=1;
}

void scena_joc::init_pereti_1(perete pereti[],int &numar_pereti)
{
    for (int i=latime_pereti_exterior+player_x; i<width-latime_pereti_exterior; i+=player_x*2)
    {
        for (int j=latime_pereti_exterior+player_y; j<hight-latime_pereti_exterior; j+=player_y*2)
        {
            pereti[++numar_pereti].forma.setPosition(sf::Vector2f(i,j));
            pereti[numar_pereti].forma.setSize(sf::Vector2f(player_x,player_y));
            //pereti[numar_pereti].forma.setFillColor(sf::Color::White);
            pereti[numar_pereti].poate_fi_explodat=0;
            pereti[numar_pereti].forma.setTexture(pzid_solid);
        }
    }
}
bool locatie_valida_perete(int i,int j)
{
    if (!(i!=latime_pereti_exterior||j!=latime_pereti_exterior))
        return 0;
    if (!(i!=latime_pereti_exterior||j!=latime_pereti_exterior+player_x))
        return 0;
    if (!(i!=latime_pereti_exterior+player_x||j!=latime_pereti_exterior))
        return 0;
    if(!(i!=width-latime_pereti_exterior-player_x||j!=hight-latime_pereti_exterior-player_y))
        return 0;
    if (!(i!=width-latime_pereti_exterior-player_x||j!=hight-latime_pereti_exterior-player_y*2))
        return 0;
    if(!(i!=width-latime_pereti_exterior-player_x*2||j!=hight-latime_pereti_exterior-player_y))
        return 0;
    if (i==width-latime_pereti_exterior-player_x&&j==latime_pereti_exterior)
        return 0;
    if (i==width-latime_pereti_exterior-player_x&&j==latime_pereti_exterior+player_y)
        return 0;
    if (i==width-latime_pereti_exterior-2*player_x&&j==latime_pereti_exterior)
        return 0;
    if (j==hight-latime_pereti_exterior-player_y&&i==latime_pereti_exterior)
        return 0;
    if (j==hight-latime_pereti_exterior-player_y&&i==latime_pereti_exterior+player_x)
        return 0;
    if (j==hight-latime_pereti_exterior-2*player_y&&i==latime_pereti_exterior)
        return 0;
    return 1;

}

void scena_joc::generare_pereti_random()
{
    srand(time(NULL));
    for (int i=latime_pereti_exterior; i<width-latime_pereti_exterior; i+=player_x)
    {
        int r;
        if (i%2==1)
            r=player_y;
        else
            r=player_y*2;
        for (int j=latime_pereti_exterior; j<hight-latime_pereti_exterior; j+=r)
        {
            if (rand()%4>0&&locatie_valida_perete(i,j)==1)
            {
                pereti[++numar_ziduri].forma.setPosition(sf::Vector2f(i,j));
                pereti[numar_ziduri].forma.setSize(sf::Vector2f(player_x,player_y));
                //pereti[numar_ziduri].forma.setFillColor(sf::Color::Cyan);
                pereti[numar_ziduri].poate_fi_explodat=1;
                pereti[numar_ziduri].forma.setTexture(pzid_fragil);
            }
        }
    }
}

void scena_joc::update_timp()
{
    int timp_trecut=ceas.getElapsedTime().asMicroseconds()-timp_frame_precedent;

    for (int i=1; i<=numar_playeri; i++)
    {
        playeri[i].cooldown_bombe-=timp_trecut;
        if (playeri[i].cooldown_bombe<0)
            playeri[i].cooldown_bombe=0;
    }
    for (int i=1; i<=numar_bombe; i++)
    {
        bombe[i].countdown-=timp_trecut;
        if (bombe[i].countdown<0)
            bombe[i].countdown=0;
    }
    for (int i=1; i<=numar_playeri; i++)
    {
        playeri[i].cooldown_miscare-=timp_trecut;
        if (playeri[i].cooldown_miscare<0)
            playeri[i].cooldown_miscare=0;
    }
    //cout << timp_trecut << endl;
    timp_frame_precedent=ceas.getElapsedTime().asMicroseconds();

}

bool scena_joc::coliziune_bomba_bomba(int indice_curent,bomba bombe[],int numar_bombe)
{
    for (int i=1; i<=numar_bombe; i++)
    {
        if (i!=indice_curent)
        {
            if (bombe[indice_curent].forma.getGlobalBounds().intersects(bombe[i].forma.getGlobalBounds())&&bombe[i].activ==1)
                return 1;
        }
    }
    return 0;
}

void scena_joc::update_particule()
{
    for (int i=1; i<=numar_particule; i++)
    {
        if (particule[i].viteza_x!=0||particule[i].viteza_y!=0)
        {
            particule[i].miscare();
            particule[i].test_colizune();
        }
    }
}

void scena_joc::draw_particule()
{
    for (int i=1; i<=numar_particule; i++)
    {
        if (particule[i].viteza_x!=0||particule[i].viteza_y!=0)
        {
            window.draw(particule[i].forma);
        }
    }
}

void scena_joc::generare_power_ups_random()
{

    //cout << "da" <<endl;
    for (int i=latime_pereti_exterior; i<width-latime_pereti_exterior; i+=player_x)
    {
        int r;
        if (i%2==1)
            r=player_y;
        else
            r=player_y*2;
        for (int j=latime_pereti_exterior; j<hight-latime_pereti_exterior; j+=r)
        {
            if (rand()%5>3&&locatie_valida_perete(i,j))
            {
                int q=rand()%4;
                power_ups[++numar_power_ups].set_position(i,j);
                power_ups[numar_power_ups].activ=1;

                if (q==0)
                {
                    power_ups[numar_power_ups].ptexture->loadFromFile("img/power_up_bomba.png");
                    power_ups[numar_power_ups].forma.setTexture(power_ups[numar_power_ups].ptexture);
                    //power_ups[numar_power_ups].set_color(sf::Color::Red);
                    power_ups[numar_power_ups].tip=0;
                    power_ups[numar_power_ups].efect_numar_bombe=1;
                }
                if (q==1)
                {
                    power_ups[numar_power_ups].ptexture->loadFromFile("img/power_up_inima.png");
                    power_ups[numar_power_ups].forma.setTexture(power_ups[numar_power_ups].ptexture);
                    //power_ups[numar_power_ups].set_color(sf::Color::Yellow);
                    power_ups[numar_power_ups].tip=1;
                    power_ups[numar_power_ups].efect_vieti=1;
                }
                if (q==2)
                {
                    power_ups[numar_power_ups].ptexture->loadFromFile("img/power_up_foc.png");
                    power_ups[numar_power_ups].forma.setTexture(power_ups[numar_power_ups].ptexture);
                    //power_ups[numar_power_ups].set_color(sf::Color::Magenta);
                    power_ups[numar_power_ups].tip=2;
                    power_ups[numar_power_ups].efect_raza=1;
                }
                if (q==3)
                {
                    power_ups[numar_power_ups].ptexture->loadFromFile("img/power_up_shoe.png");
                    power_ups[numar_power_ups].forma.setTexture(power_ups[numar_power_ups].ptexture);
                    //power_ups[numar_power_ups].set_color(sf::Color::Green);
                    power_ups[numar_power_ups].tip=3;
                    power_ups[numar_power_ups].efect_viteza=1;
                }
            }
        }
    }
}

void scena_joc::draw_power_ups()
{
    for (int i=1; i<=numar_power_ups; i++)
        if (power_ups[i].activ==1)
        {
            window.draw(power_ups[i].forma);
        }
}

void scena_joc::update_power_ups()
{
    for (int i=1; i<=numar_playeri; i++)
    {
        for (int j=1; j<=numar_power_ups; j++)
        {
            if (power_ups[j].activ==1)
                if (playeri[i].forma.getGlobalBounds().intersects(power_ups[j].forma.getGlobalBounds()))
                {
                    power_ups[j].activ=0;
                    playeri[i].bombe_ramase+=power_ups[j].efect_numar_bombe;
                    playeri[i].powerup_miscare+=power_ups[j].efect_viteza;
                    playeri[i].inghetat+=power_ups[j].efect_vieti;
                    playeri[i].dimensiune_explozie+=power_ups[j].efect_raza;
                }
        }
    }
}

void switch_text(int x,sf::RectangleShape &text)
{
    switch (x)
    {
    case 0:
    {
        text.setTexture(pt0);
        break;
    }
    case 1:
    {
        text.setTexture(pt1);
        break;
    }
    case 2:
    {
        text.setTexture(pt2);
        break;
    }
    case 3:
    {
        text.setTexture(pt3);
        break;
    }
    case 4:
    {
        text.setTexture(pt4);
        break;
    }
    case 5:
    {
        text.setTexture(pt5);
        break;
    }
    case 6:
    {
        text.setTexture(pt6);
        break;
    }
    case 7:
    {
        text.setTexture(pt7);
        break;
    }
    case 8:
    {
        text.setTexture(pt8);
        break;
    }
    case 9:
    {
        text.setTexture(pt9);
        break;
    }
    }
}

void f(player playeri[],int indice,sf::RectangleShape &text,int r)
{
    int x;

    text.setPosition(sf::Vector2f(width+40+r,10));
    x=playeri[indice].inghetat;
    switch_text(x,text);
    if (playeri[indice].inghetat<=0)
    {
        text.setTexture(pt0);
    }
    window.draw(text);


    text.setPosition(sf::Vector2f(width+40+r,35));
    x=playeri[indice].bombe_ramase;
    switch_text(x,text);
    if (playeri[indice].inghetat<=0)
    {
        text.setTexture(pt0);
    }
    window.draw(text);


    text.setPosition(sf::Vector2f(width+40+r,60));
    x=playeri[indice].dimensiune_explozie;
    switch_text(x,text);
    if (playeri[indice].inghetat<=0)
    {
        text.setTexture(pt0);
    }
    window.draw(text);


    text.setPosition(sf::Vector2f(width+40+r,85));
    x=playeri[indice].powerup_miscare;
    switch_text(x,text);
    if (playeri[indice].inghetat<=0)
    {
        text.setTexture(pt0);
    }
    window.draw(text);
}


void scena_joc::afisare_statistici()
{
    sf::RectangleShape q;
    q.setSize(sf::Vector2f(25,25));

    q.setTexture(pt_inima);
    q.setPosition(sf::Vector2f(width+10,10));
    window.draw(q);

    q.setTexture(pt_bomba);
    q.setPosition(sf::Vector2f(width+10,35));
    window.draw(q);

    q.setTexture(pt_foc);
    q.setPosition(sf::Vector2f(width+10,60));
    window.draw(q);

    q.setTexture(pt_shoe);
    q.setPosition(sf::Vector2f(width+10,85));
    window.draw(q);


    sf::RectangleShape text;
    text.setSize(sf::Vector2f(20,20));

    for (int i=1; i<=numar_playeri; i++)
    {
        f(playeri,i,text,(i-1)*25);
    }
    for (int i=1; i<=numar_playeri;i++)
    {
        q.setSize(sf::Vector2f(20,20));
        q.setTexture(playeri[i].forma.getTexture());
        q.setPosition(sf::Vector2f(width+40+(i-1)*25,110));
        window.draw(q);
    }



    /////////////////////////////////////////////////////////
}
