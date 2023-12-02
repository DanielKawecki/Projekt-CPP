#include <SFML/Graphics.hpp>
#include <iostream>
#include "application.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "AStar.h"

int main()
{
    MyApplication App;
    Player Player(App);
    //App.createEnemy(900.f, 100.f);
    App.setupMap();
    AStar AStar(App.getAStarTiles());
    std::vector<Tile*> path = AStar.findPath(App.getTile(1, 1), App.getTile(2, 3));
    std::cout << "Path: ";
    for (Tile* tile : path) {
        std::cout << tile->getX() << tile->getY() << " ";
    }


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
        //App.updateAllBullets(App.getDeltaTime());
        App.updateAllEnemies(Player.getX(), Player.getY(), App.getDeltaTime());
        App.updateAllBodies();
        Player.move(App.getDeltaTime(), App.getTileVector());
        App.updateView(Player.getX(), Player.getY());
        App.updateFPS();
        Player.look(App.getWindow(), App.getView());
        
        App.drawingFunction(Player.draw(), Player.getLegsSprite());
    }

    return 0;
}