#include "bomba.h"
#include "init.h"

void adaugare_particula(int x,int y,float viteza_x,float viteza_y,int unghi,int countdown,sf::RectangleShape border,particula particule[],int &numar_particule);

int numar_particule_per_explozie=30;
bomba::bomba()
{
    ptexture=new sf::Texture;
    ptexture->loadFromFile("img/bomba.png");
    forma.setTexture(ptexture);
    forma.setSize(sf::Vector2f(bomba_x,bomba_y));
    //forma.setFillColor(sf::Color(255,165,2));
}

bomba::~bomba()
{
    delete ptexture;
}

void bomba::set_position(int x,int y)
{
    forma.setPosition(sf::Vector2f(x,y));
}

void bomba::set_dimensiune_explozie(int x)
{
    dimensiune_explozie=x;
}


void bomba::explodare(perete pereti[],player playeri[],int numar_pereti,int numar_playeri,bomba bombe[],int numar_bombe,particula particule[],int &numar_particule)
{

    int x=forma.getPosition().x;
    int y=forma.getPosition().y;

    int size_x=forma.getSize().x;
    int size_y=forma.getSize().y;

    proprietar->bombe_ramase+=1;
    int p[5]={0};
    verificare_explozie(x,y,pereti,playeri,numar_pereti,numar_playeri,bombe,numar_bombe,particule,numar_particule,p);

    for (int i=1; i<=dimensiune_explozie; i++) // IN STANGA
    {
        int x_nou=x-size_x*i;
        int y_nou=y;


        if (verificare_explozie(x_nou,y_nou,pereti,playeri,numar_pereti,numar_playeri,bombe,numar_bombe,particule,numar_particule,p))
            break;

    }
    for (int i=1; i<=dimensiune_explozie; i++) // IN DREAPTA
    {
        int x_nou=x+size_x*i;
        int y_nou=y;
        if (verificare_explozie(x_nou,y_nou,pereti,playeri,numar_pereti,numar_playeri,bombe,numar_bombe,particule,numar_particule,p))
            break;
    }
    for (int i=1; i<=dimensiune_explozie; i++) // IN JOS
    {
        int x_nou=x;
        int y_nou=y+size_y*i;
        if (verificare_explozie(x_nou,y_nou,pereti,playeri,numar_pereti,numar_playeri,bombe,numar_bombe,particule,numar_particule,p))
            break;
    }
    for (int i=1; i<=dimensiune_explozie; i++) // IN SUS
    {
        int x_nou=x;
        int y_nou=y-size_y*i;
        if (verificare_explozie(x_nou,y_nou,pereti,playeri,numar_pereti,numar_playeri,bombe,numar_bombe,particule,numar_particule,p))
            break;
    }
    activ=0;

}
bool bomba::verificare_explozie(int x_nou,int y_nou,perete pereti[],player playeri[],int numar_pereti,int numar_playeri,bomba bombe[],int numar_bombe,particula particule[],int &numar_particule,int p[])
{
    int size_x=forma.getSize().x;
    int size_y=forma.getSize().y;

    sf::RectangleShape b;
    b.setPosition(sf::Vector2f(x_nou+5,y_nou+5));
    b.setSize(sf::Vector2f(size_x-10,size_y-10));

    for (int j=1; j<=numar_pereti; j++)
    {
        if (b.getGlobalBounds().intersects(pereti[j].forma.getGlobalBounds()))
        {
            if (pereti[j].poate_fi_explodat==1)
            {
                pereti[j].forma.setSize(sf::Vector2f(0,0));
                explozie(numar_particule_per_explozie,x_nou+forma.getSize().x/2,y_nou+forma.getSize().y/2,b,particule,numar_particule);

                return 1;
                j=numar_pereti+1;
                break;
            }
            else
            {
               return 1;
                break;
            }
        }
    }
    explozie(numar_particule_per_explozie,x_nou+forma.getSize().x/2,y_nou+forma.getSize().y/2,b,particule,numar_particule);

    for (int j=1; j<=numar_playeri; j++)
    {
        if (b.getGlobalBounds().intersects(playeri[j].forma.getGlobalBounds())&&p[j]==0)
        {
            p[j]=1;
            playeri[j].inghetat--;
        }
    }

    for (int i=1;i<=numar_bombe;i++)
    {
        if (bombe[i].forma.getPosition()!=this->forma.getPosition())
        {
            if (b.getGlobalBounds().intersects(bombe[i].forma.getGlobalBounds())&&bombe[i].activ==1)
            {
                bombe[i].activ=0;
                bombe[i].explodare(pereti,playeri,numar_pereti,numar_playeri,bombe,numar_bombe,particule,numar_particule);

            }
        }
    }

    return 0;
}

void bomba::explozie(int numar_particule_explozie,int x,int y,sf::RectangleShape border,particula particule[],int &numar_particule)
{
    //srand(time(NULL));
    for (int i=1;i<=numar_particule_explozie;i++)
    {
        int unghi=rand()%360;
        adaugare_particula(x,y,0.5,0.5,unghi,1000000,border,particule,numar_particule);
    }
}
