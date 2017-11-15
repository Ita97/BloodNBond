//
// Created by ita on 01/11/17.
//
#include "Character.h"

Character& Character::operator=(const Character &right) {
    if(this != &right) {
        if(weapon != nullptr)
            delete weapon;
        copier(right);
    }
    return *this;

}
Character& Character::copier(const Character &original) {
    hp=original.hp;
    posY=original.posY;
    posX=original.posX;
    if(original.weapon!= nullptr)
        weapon=original.weapon->clone();
    else
        weapon= nullptr;
}
Character::Character(const Character &original) {
    copier(original);
}