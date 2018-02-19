//
// Created by ita on 01/11/17.
//

#ifndef BLOODBOND_ENEMY_H
#define BLOODBOND_ENEMY_H


#include <SFML/Graphics/Sprite.hpp>
#include "Character.h"
#include "Weapon.h"

enum class EnemyType{skeleton, dragon};
enum class Behavior{berserk, sniper, std };


class Enemy:virtual public Character{
public:
    Enemy(int hp, int x, int y, int stg, EnemyType type, Behavior behavior);
    std::string getAbility(){
        return ability;
    }
    int getStrength(){
        return strength;
    }
    void move(Character& character);
    void move() override;
    void attack(Character& character);
    void Render(Window& l_window) override;
    bool shootingLine(float x, float y);
    sf::Vector2f getFeetPosition() override;
    sf::Vector2f getRange(){
        return range;
    }
    bool isSniper(){
        return behavior == Behavior::sniper;
    }
    bool isBerserker(){
        return behavior==Behavior ::berserk;
    }
    bool hit;
    void use() {
        if (isSniper()) {
            weapon->use();
            if (walk == 0)
                fireBall.setRotation(180);
            else if (walk == 1)
                fireBall.setRotation(90);
            else if (walk == 2)
                fireBall.setRotation(0);
            else if (walk == 3)
                fireBall.setRotation(270);

            if (!weapon->checkCollision(getPosition(), range, fireBall.getPosition()))
                fight = false;
            else
                fireBall.setPosition(weapon->getPosition());
        }
    }
private:
    EnemyType category;
    Behavior behavior;
    std::string ability;
    int strength;
    sf::Vector2f range,speed;
    float walkSpeed, attackFrame;
    sf::Texture fireBall_t;
    sf::Sprite fireBall;
    bool fight;
};


#endif //BLOODBOND_ENEMY_H
