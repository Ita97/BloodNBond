//
// Created by ita on 01/11/17.
//

#ifndef BLOODBOND_ENEMY_H
#define BLOODBOND_ENEMY_H


#include <SFML/Graphics/Sprite.hpp>
#include "Character.h"
#include "Weapon.h"

class Enemy:virtual public Character{
public:
    Enemy(int hp, int x, int y, Weapon* weapon);
    void move() override;
    void attack() override;
    void Render(Window& l_window) override;

private:
    sf::Texture t_enemy;
    sf::Sprite enemy;
    float frame=1;
};


#endif //BLOODBOND_ENEMY_H
