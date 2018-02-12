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
            hp(h),posX(x),posY(y), weapon(w){}

    virtual ~Character()= default;

    virtual void move()=0;
    virtual void attack()=0;

    virtual void Render(Window& l_window)=0;

    int getHp(){
        return hp;
    }
    void heal(int value){
        Character::hp+=value;
    }

    void damage(int value){
        Character::hp-=value;
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
        return sf::Vector2f(posX,posY);
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
protected:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f collisionArea;
    int hp;
    float frame;
    float posX, posY;
    Weapon* weapon;
    int walk;

};


#endif //BLOODBOND_CHARACTER_H
