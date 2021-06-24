#include "scena_meniu.h"
#include <cstring>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "init.h"


void scena_meniu::adaugare_optiune(const char *s)
{
    strcpy(optiuni[++numar_optiuni],s);
}

void scena_meniu::input_tastatura()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type==sf::Event::KeyReleased)
        {
            if (event.key.code==sf::Keyboard::Up)
            {
                up=1;
                down=0;
            }

            if (event.key.code==sf::Keyboard::Down)
            {
                up=0;
                down=1;
            }

            if (event.key.code==sf::Keyboard::Enter)
            {
                enter=1;
            }
            if (event.key.code==sf::Keyboard::Left)
            {
                left=1;
                right=0;
            }
            if (event.key.code==sf::Keyboard::Right)
            {
                right=1;
                left=0;
            }

        }

        if (event.type==sf::Event::Closed)
        {
            game_on=0;
        }
    }
}

void scena_meniu::deplasare()
{
    if (up==1)
    {
        optiune_curenta--;
        if(optiune_curenta==0)
            optiune_curenta=1;
        up=0;
    }
    if (down==1)
    {
        optiune_curenta++;
        if (optiune_curenta==numar_optiuni+1)
            optiune_curenta=numar_optiuni;
        down=0;
    }
    if (enter==1)
    {
        actiune();
        enter=0;
    }
    if (right)
    {
        numar_playeri++;
        if (numar_playeri>4)
            numar_playeri=4;
        right=0;
    }
    if (left)
    {
        numar_playeri--;
        if (numar_playeri<2)
            numar_playeri=2;
        left=0;
    }
}

void scena_meniu::draw()
{
    window.clear();
    window.draw(sprite_harta);
    afisare_optiuni();
    afisare_playeri();
    window.display();
}

void scena_meniu::afisare_optiuni()
{
    int x_optiuni=200;
    int y_optiuni=hight/2-numar_optiuni*50;
    for (int i=1; i<=numar_optiuni; i++)
    {
        sf::Text text;
        text.setString(optiuni[i]);
        text.setCharacterSize (80);
        text.setPosition(sf::Vector2f(x_optiuni,y_optiuni));
        y_optiuni+=90;
        text.setFillColor(sf::Color::White);
        if (optiune_curenta==i)
            text.setFillColor(sf::Color(100,255,0));
        sf::Font arial;
        arial.loadFromFile ("arial.ttf");
        text.setFont (arial);
        text.setOutlineColor(sf::Color::Black);
        text.setOutlineThickness(1);
        window.draw(text);
    }
}

void scena_meniu::update()
{
    input_tastatura();
    deplasare();
    draw();
}

void scena_meniu::actiune()
{
    if (strstr(optiuni[optiune_curenta],"PLAY"))
    {
        scena_curenta=2;
        joc_principal.reset(numar_playeri);
    }
    if (strstr(optiuni[optiune_curenta],"EXIT"))
    {
        game_on=0;
    }

}

void scena_meniu::afisare_playeri()
{
    sf::RectangleShape sprite;

    sprite.setSize(sf::Vector2f(30,30));
    sprite.setTexture(p_player1_dreapta);
    sprite.setPosition(latime_pereti_exterior,latime_pereti_exterior);
    window.draw(sprite);


    sprite.setTexture(p_player2_stanga);
    sprite.setPosition(width-latime_pereti_exterior-player_x,hight-latime_pereti_exterior-player_y);
    window.draw(sprite);

    if (numar_playeri>2)
    {
        sprite.setTexture(p_player3_dreapta);
        sprite.setPosition(latime_pereti_exterior,hight-latime_pereti_exterior-player_y);
        window.draw(sprite);
    }
    if (numar_playeri>3)
    {
        sprite.setTexture(p_player4_stanga);
        sprite.setPosition(width-latime_pereti_exterior-player_x,latime_pereti_exterior);
        window.draw(sprite);
    }
}
