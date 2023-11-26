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
    //App.createEnemy(700.f, 600.f);
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            App.createTile(i*48, j*48);
        }
    }

    //sf::RenderWindow window(sf::VideoMode(App.getScreenWidth(), App.getScreenHeight()), "SFML works!");

    while (App.getWindow().isOpen())
    {
        sf::Event event;
        while (App.getWindow().pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                App.getWindow().close();
        }

        //window.setFramerateLimit(120);

        App.setDeltaTime();

        //App.spawn();
        App.updateAllBullets(App.getDeltaTime());
        App.updateAllEnemies(Player.getX(), Player.getY(), App.getDeltaTime());
        App.updateAllBodies();
        Player.move(App.getDeltaTime());
        App.updateView(Player.getX(), Player.getY());
        App.updateFPS();
        Player.look(App.getWindow(), App.getView());
        
        App.drawingFunction(Player.draw(), Player.getLegsSprite());
    }

    return 0;
}