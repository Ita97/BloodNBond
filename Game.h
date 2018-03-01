//
// Created by ita on 30/08/17.
//

#ifndef BLOODBOND_GAME_H
#define BLOODBOND_GAME_H
#include <SFML/Graphics.hpp>
#include "Character.h"
#include "Detective.h"
#include "Map.h"
#include "EnemyFactory.h"

class Game {
public:
    Game();
    ~Game(){}

    void GameStart();

private:
    void handelInput();
    void update();
    void GameLoop();
    bool checkCollision(sf::Vector2f target, sf::Vector2f collisionArea,sf::Vector2f focus, sf::Vector2f range);
    void gameBound();
    void initialize();
    void end();
    void insertMap(MapType type){
        currencyMap=new Map(type);
        map.push_back(currencyMap);
    }

    sf::Texture home, credit;
    sf::Sprite sprite;
    sf::RenderWindow window;
    sf::Time txtTime;
    sf::Clock gameClock;
    sf::Font msg, old;
    sf::Text text;
    Detective jack;
    std::vector<Enemy*> enemyFolder;
    EnemyFactory *deadFactory;
    Map* currencyMap;
    std::vector<Map*> map;
    bool round_1,round_2, boxOpen_1,boxOpen_2;

};


#endif //BLOODBOND_GAME_H
