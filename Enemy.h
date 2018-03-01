//
// Created by ita on 01/11/17.
//

#ifndef BLOODBOND_ENEMY_H
#define BLOODBOND_ENEMY_H

#include <SFML/Graphics.hpp>
#include "Character.h"
#include "Weapon.h"
#include "Subject.h"

enum class EnemyType{skeleton, dragon};
enum class Behavior{berserk, sniper, std };


class Enemy:virtual public Character,virtual public Subject{
public:
    Enemy(int hp, int x, int y, int stg, EnemyType type, Behavior behavior);
    ~Enemy(){
        notify();
        unsubscrive(det);
    }
    std::string getAbility(){
        return ability;
    }
    int getStrength(){
        return strength;
    }
    void move(Character& character);
    void move() override;
    void attack(Character& character);
    void Render(sf::RenderWindow& l_window) override;
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
    void use() {
        if (isSniper()) {
            if(fight){
                weapon->use();
                if (!weapon->checkCollision(getPosition(), range, fireBall.getPosition())) {
                    fireBall.setPosition(-100, -100);
                    fight = false;
                }
                else
                    fireBall.setPosition(weapon->getPosition());
            }
        }
    }


    void subscribe(Observer *o) override{
        det=o;
    }
    void unsubscrive(Observer *o) override{
        o= nullptr;
    }
    void notify() override{
        det->update();
    }
private:
    EnemyType category;
    Behavior behavior;
    std::string ability;
    int strength;
    sf::Vector2f range,speed;
    sf::Vector2i frameSize,size;
    int frameCount;
    float walkSpeed, attackFrame;
    sf::Texture fireBall_t;
    sf::Sprite fireBall;
    Observer *det;
};


#endif //BLOODBOND_ENEMY_H
