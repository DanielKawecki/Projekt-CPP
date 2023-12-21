#include <SFML/Graphics.hpp>
#include <iostream>
#include "application.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "BFS.h"

int main()
{
    MyApplication App;
    Player Player(App);
    //App.createEnemy(300.f, 100.f);
    //App.createEnemy(400.f, 500.f);
    App.setupMap();
    App.setupOverlay();

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
        App.updateView(Player.getX(), Player.getY());

        if (!App.isPause()) {
            App.spawn();
            App.updateAllEnemies(Player.getX(), Player.getY(), App.getDeltaTime());
            App.updateAllBodies();

            if (!App.isGameOver()) {
                Player.move(App.getDeltaTime(), App.getTileVector(), App.getEnemiesVector());
                Player.look(App.getWindow(), App.getView());
            }

            Player.checkEnemies();
        }
        
        if (!App.isGameOver())
            App.setPause();
        else {
            if (App.checkForReset()) {
                Player.setHealth(100);
                Player.resetPos();
            }
        }

        App.updateFPS();
        App.updateHealth(Player.getHealth());
        
        App.drawingFunction(Player.draw(), Player.getLegsSprite());
    }

    return 0;
}