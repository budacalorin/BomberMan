#ifndef PARTICULA
#define PARTICULA

#include <SFML/Graphics.hpp>

class particula{
public:
    sf::RectangleShape forma;
    float viteza_x,viteza_y;
    int countdown;
    sf::RectangleShape border;
    int unghi;

    particula();

    void setup(int x,int y,float viteza_Y,float viteza_X,int UNGHI, int COUNTDOWN,sf::RectangleShape BORDER);

    void miscare();

    void test_colizune();
};

#endif // PARTICULA
