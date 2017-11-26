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
    virtual void attack(Character& enemy)=0;

    void Render(Window& l_window);

    int getHp(){
        return hp;
    }
    void heal(int value){
        Character::hp+=value;
    }

    void hit(int value){
        Character::hp-=value;
    }

    float getPosX(){
        return posX;
    }
    float getPosY(){
        return posY;
    }
    sf::Vector2f getPosition(){
        return sf::Vector2f(posX,posY);
    }
    Weapon* getWeapon(){
        return weapon;
    }
    void setWeapon(Weapon* weapon){
        Character::weapon=weapon;
    }
    Character& operator =(const Character& right);
    Character& copier(const Character& original);

    sf::Vector2f getCollisionArea(){
        return collisionArea;
    }
    void screenBound();
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
