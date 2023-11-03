#include <SFML/Graphics.hpp>
#include <iostream>
#include "application.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"

int main()
{
    MyApplication App;
    Player Player(App);
    App.createEnemy();

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

        App.drawing_function(window, Player.draw(), Player.getLegsSprite());
    }

    return 0;
}