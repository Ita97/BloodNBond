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
    virtual ~Character(){}

    virtual void move()=0;
    virtual void attack(Character& enemy)=0;
    virtual void Render(Window& l_window)=0;
    int getHp(){
        return hp;
    }
    void setHp(int value){
        Character::hp+=value;
    }

    int getPosX(){
        return posX;
    }
    int getPosY(){
        return posY;
    }

    Weapon* getWeapon(){
        return weapon;
    }
    void setWeapon(Weapon* weapon){
        Character::weapon=weapon;
    }
    Character& operator =(const Character& right);
    Character& copier(const Character& original);
protected:
    int hp;
    float frame;
    float posX, posY;
    Weapon* weapon;

};


#endif //BLOODBOND_CHARACTER_H
