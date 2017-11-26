//
// Created by ita on 01/11/17.
//
#include "Character.h"

Character& Character::operator=(const Character &right) {
    if(this != &right) {
        if(weapon != nullptr)
            delete[] weapon;
        copier(right);
    }
    return *this;

}
void Character::screenBound() {
    if(posX<=collisionArea.x) posX=collisionArea.x;
    if(posX+collisionArea.x>=960) posX=960-collisionArea.x;
    if(posY<=collisionArea.y*3/2) posY=collisionArea.y*3/2;
    if(posY+collisionArea.y*3/2>=480) posY=480-collisionArea.y*3/2;
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

void Character::Render(Window &l_window) {
    l_window.Draw(sprite);
}
