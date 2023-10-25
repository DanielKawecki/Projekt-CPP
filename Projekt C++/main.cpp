#include <SFML/Graphics.hpp>
#include <iostream>
#include "application.h"
#include "player.h"

int main()
{
    MyApplication App;
    Player Player;

    Player.setup();

    sf::RenderWindow window(sf::VideoMode(App.getScreenWidth(), App.getScreenHeight()), "SFML works!");

    App.getDeltaTime();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        Player.move(App.getDeltaTime().asSeconds());
        Player.look(window);

        App.drawing_function(window, Player.draw());
    }

    return 0;
}