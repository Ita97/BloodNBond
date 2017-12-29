//
// Created by ita on 29/12/17.
//

#ifndef BLOODBOND_ENEMYFACTORY_H
#define BLOODBOND_ENEMYFACTORY_H

#include "Enemy.h"
enum class level{low, medium, high};

class EnemyFactory {
private:
    EnemyType factoryType;
    level factoryPower;
    sf::Vector2i factoryPosition;

public:
    EnemyFactory(EnemyType enemyType, level power, sf::Vector2i position):
            factoryType(enemyType),factoryPower(power),factoryPosition(position){}
    ~EnemyFactory(){}
    Enemy* CreateEnemy() const;
};


#endif //BLOODBOND_ENEMYFACTORY_H
