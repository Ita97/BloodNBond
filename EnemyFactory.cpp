//
// Created by ita on 29/12/17.
//

#include "EnemyFactory.h"

Enemy* EnemyFactory::CreateEnemy() const {
    switch (factoryPower){
        case level::low:
            return new Enemy(50,factoryPosition.x,factoryPosition.y,5, nullptr,factoryType);
            break;
        case level::medium:
            return new Enemy(70,factoryPosition.x,factoryPosition.y,10, nullptr,factoryType);
            break;
        case level ::high:
            return new Enemy(100,factoryPosition.x,factoryPosition.y,20, nullptr,factoryType);
            break;
    }
}