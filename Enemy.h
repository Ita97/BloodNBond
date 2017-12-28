//
// Created by ita on 01/11/17.
//

#ifndef BLOODBOND_ENEMY_H
#define BLOODBOND_ENEMY_H


#include <SFML/Graphics/Sprite.hpp>
#include "Character.h"
#include "Weapon.h"

enum class EnemyType{zombie, ghost, dragon};


class Enemy:virtual public Character{
public:
    Enemy(int hp, int x, int y, int stg, Weapon* weapon, EnemyType type);
    std::string getAbility(){
        return ability;
    }
    int getStrength(){
        return strength;
    }
    void move() override;
    void attack(Character& enemy) override;
    void Render(Window& l_window) override;

private:
    EnemyType category;
    std::string ability;
    int strength;
};


#endif //BLOODBOND_ENEMY_H
