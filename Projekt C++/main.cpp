#include <SFML/Graphics.hpp>
#include <iostream>
#include "application.h"
#include "player.h"

int main()
{
    MyApplication App;
    Player Player;

    sf::RenderWindow window(sf::VideoMode(App.getScreenWidth(), App.getScreenHeight()), "SFML works!");

    App.getDeltaTime();
    //App.add_to_vecor();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        Player.move(App.getDeltaTime().asSeconds());
        //std::cout << App.getDeltaTime().asSeconds() << "\n";

        App.drawing_function(window, Player.draw());
    }

    return 0;
}