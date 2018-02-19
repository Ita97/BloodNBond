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
#include "EnemyFactory.h"

class Game {
public:
    Game();
    ~Game(){}

    void handelInput();
    void update();
    void GameStart();
    void gameLoop();
    bool checkCollision(sf::Vector2f target, sf::Vector2f collisionArea,sf::Vector2f focus, sf::Vector2f range);
    void gameBound();
private:
    Window window;
    sf::Clock gameClock;
    sf::Font msg, old;
    sf::Text detStatus, enemyStatus;
    Detective jack;
    Enemy *enemy;
    std::vector<Enemy*> enemyFolder;
    EnemyFactory *deadFactory;
    Map* currencyMap;
    std::vector<Map*> map;
    void insertMap(MapType type){
        currencyMap=new Map(type);
        map.push_back(currencyMap);
    }

};


#endif //BLOODBOND_GAME_H
