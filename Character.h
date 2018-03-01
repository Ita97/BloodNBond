//
// Created by ita on 14/09/17.
//

#ifndef BLOODBOND_CHARACTER_H
#define BLOODBOND_CHARACTER_H

#include <SFML/Graphics/RenderWindow.hpp>
#include "Weapon.h"
#include "Medicine.h"
#include "Window.h"
class Character {
public:
    Character(const Character& original);
    explicit Character(int h, int x=0, int y=0, Weapon* w= nullptr):
            healtPoint(h),posX(x),posY(y), weapon(w){
        isRender=false;
    }

    virtual void move()=0;

    virtual void Render(sf::RenderWindow& l_window)=0;

    int getHp(){
        return healtPoint;
    }


    void damage(int value){
        if(value>0) {
            Character::healtPoint -= value;
            if(healtPoint<0)
                healtPoint=0;
        }
    }

    float getPosX(){
        return posX;
    }
    void setPosX(float pos){
        posX=pos;
        sprite.setPosition(pos,posY);
    }
    float getPosY(){
        return posY;
    }
    void setPosY(float pos){
        posY=pos;
        sprite.setPosition(posX,pos);
    }
    sf::Vector2f getPosition(){
        return {posX,posY};
    }
    void setPosition(sf::Vector2f position){
        posX=position.x;
        posY=position.y;
        sprite.setPosition(position);
    }
    Character& operator =(const Character& right);
    Character& copier(const Character& original);

    sf::Vector2f getCollisionArea(){
        return collisionArea;
    }
    int getDirection(){
        return walk;
    }
    sf::Vector2f getWalkingArea(){
        return walkingArea;
    }
    sf::Vector2f getAttackRange(){
        if(weapon!= nullptr)
            return weapon->getCollisionArea();
        return  collisionArea;
    }
    sf::Vector2f getAttackPosition(){
        if(weapon!= nullptr)
            return weapon->getPosition();
        return getPosition();
    }
    virtual sf::Vector2f getFeetPosition()=0;
    void resetRender(){
        isRender=false;
    }
    bool getRender(){
        return isRender;
    }

    bool isFighting() {
        return fight;
    }

    bool ready(){
        if(weapon!= nullptr)
            return weapon->isReady();
        return fight;
    }

    void hit(){
        if(weapon!= nullptr)
            weapon->disable();
    }

protected:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f collisionArea;
    sf::Vector2f walkingArea;
    int healtPoint;
    float frame;
    float posX, posY;
    Weapon* weapon;
    int walk;
    bool isRender;
    bool fight;


};



#endif //BLOODBOND_CHARACTER_H
