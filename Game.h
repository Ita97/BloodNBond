//
// Created by ita on 30/08/17.
//

#ifndef BLOODBOND_GAME_H
#define BLOODBOND_GAME_H

#include <SFML/Graphics.hpp>
#include "Window.h"
#include "Character.h"
#include "Detective.h"
#include "Utilities.h"
#include "Map.h"

class Game {
public:
    Game();
    ~Game(){}

    void handelInput();
    void update();
    void GameStart();
    void gameLoop();
    bool checkCollision(sf::Vector2f target, sf::Vector2f collisionArea,sf::Vector2f focus, sf::Vector2f range) {
        if(focus.x+range.x/2>target.x-collisionArea.x/2 && focus.x-range.x/2<target.x+collisionArea.x/2)
            if(focus.y+range.y/2>target.y-collisionArea.y/2 && focus.y-range.y/2<target.y+collisionArea.y/2)
                return true;
        return false;

    }
    void gameBound();
    //...TODO
private:
    Window window;
    sf::Clock gameClock;
    sf::Font msg, old;
    sf::Text detStatus, enemyStatus;
    Detective jack;
    Enemy *enemy;
    std::vector<Enemy*> enemyFolder;
    Map map;

};


#endif //BLOODBOND_GAME_H
