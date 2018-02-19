//
// Created by ita on 29/12/17.
//

#include "EnemyFactory.h"

Enemy* EnemyFactory::CreateEnemy(Behavior behavior) const {
    int lvl;
    switch (factoryPower){
        case level::low:
            lvl=15;
            break;
        case level::medium:
            lvl=40;
            break;
        case level ::high:
            lvl=70;
            break;
    }
    return new Enemy(lvl,factoryPosition.x,factoryPosition.y,lvl/5,factoryType,behavior);
}