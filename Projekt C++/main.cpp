#include <SFML/Graphics.hpp>
#include "application.h"

int main()
{
    MyApplication App;

    sf::RenderWindow window(sf::VideoMode(App.getScreenWidth(), App.getScreenHeight()), "SFML works!");
    
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    App.add_to_vecor(shape);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        App.drawing_function(window);
    }

    return 0;
}