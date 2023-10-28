#include <SFML/Graphics.hpp>
#include <iostream>
#include "application.h"
#include "player.h"
#include "bullet.h"

int main()
{
    MyApplication App;
    Player Player(App);
    //Bullet bull = Bullet(100, 100, 30.f, 0);
    //App.add_to_vecor(bull);

    Player.setup();

    sf::RenderWindow window(sf::VideoMode(App.getScreenWidth(), App.getScreenHeight()), "SFML works!");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        App.setDeltaTime();

        App.update_all_bullets(App.getDeltaTime());
        Player.move(App.getDeltaTime());
        Player.look(window);

        App.drawing_function(window, Player.draw());
    }

    return 0;
}