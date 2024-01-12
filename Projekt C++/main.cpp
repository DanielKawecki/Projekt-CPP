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

        if (!App.gameStarted()) {
            App.updateView(App.getScreenWidth()/2.f, App.getScreenHeight()/2.f);
            App.drawStartingScreen(event);
        }

        else {

            App.setDeltaTime();
            App.updateView(Player.getX(), Player.getY());

            if (!App.isPause()) {
                App.spawn();
                App.updateAllEnemies(Player.getX(), Player.getY(), App.getDeltaTime());
                App.updateAllBodies();

                if (!App.isGameOver()) {
                    Player.move(App.getDeltaTime(), App.getTileVector(), App.getEnemiesVector());
                    Player.look(App.getWindow(), App.getView());
                    App.updateAmmo(Player.getAmmo());
                    if (App.checkHealthRefill(Player.getRect()))
                        Player.addHealth(20);
                    if (App.checkAmmoRefill(Player.getRect()))
                        Player.addAmmo(30);
                }

                Player.checkEnemies();
            }
            else {
                if (App.checkForReset()) {
                    Player.setHealth(100);
                    Player.resetPos();
                    Player.resetAmmo();
                    App.setReset(false);
                }
            }

            if (!App.isGameOver())
                App.setPause();
            else {
                if (App.checkForReset()) {
                    Player.setHealth(100);
                    Player.resetPos();
                    Player.resetAmmo();
                    App.setReset(false);
                    
                }
            }

            if (App.isGameOver())
                App.checkBestScore();

            App.updateFPS();
            App.updateHealth(Player.getHealth());

            App.drawingFunction(Player.draw(), Player.getLegsSprite(), Player.getReloadRect(), event);
        }
    }

    return 0;
}