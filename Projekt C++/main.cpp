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
    App.createEnemy(900.f, 100.f);
    App.createEnemy(700.f, 600.f);

    sf::RenderWindow window(sf::VideoMode(App.getScreenWidth(), App.getScreenHeight()), "SFML works!");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //window.setFramerateLimit(120);

        App.setDeltaTime();

        App.updateAllBullets(App.getDeltaTime());
        App.updateAllEnemies(Player.getX(), Player.getY(), App.getDeltaTime());
        App.updateAllBodies();
        Player.move(App.getDeltaTime());
        App.updateText();
        Player.look(window);

        App.drawingFunction(window, Player.draw(), Player.getLegsSprite());
    }

    return 0;
}