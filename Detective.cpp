//
// Created by ita on 14/09/17.
//

#include <iostream>
#include "Detective.h"



Detective::Detective(const std::string& name,int h, int sp, int ap, int x, int y, Weapon* w):
        name(name), Character(h, x, y, w), sanityPoint(sp), abilityPoint(ap){
    texture.loadFromFile("/home/ita/CLionProjects/BloodBond/pic/sprite/first-detective.png");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0,0,73,110)); //left, top, width, length
    sprite.setOrigin(73/2,110/2);
    sprite.setPosition(x,y);
    frame=0;
    walk=0;
    collisionArea=sf::Vector2f(40,110/3);
}


void Detective::move() {

    float walkSpeed=0.015;
    int frameCount=5;
    float speedX=0.72, speedY=0.42;
    int x=69, y=103, w=73, l=110;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))  { //down
        walk=0;
        if(static_cast<int>(frame)==1 || static_cast<int>(frame)==3)
            posY+=speedY;
        frame+=walkSpeed;
        if(frame>=frameCount)
            frame=1;
        sprite.setTextureRect(sf::IntRect(static_cast<int>(frame)*x,walk*y,w,l));
    }

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { //right
        walk=1;
        if(static_cast<int>(frame)==1 || static_cast<int>(frame)==3)
            posX+=speedX;
        frame+=walkSpeed;
        if(frame>=frameCount)
            frame=1;
        sprite.setTextureRect(sf::IntRect(static_cast<int>(frame)*x,walk*y,w,l));
    }

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){ //up
        walk=2;
        if(static_cast<int>(frame)==1 || static_cast<int>(frame)==3)
            posY-=speedY;
        frame+=walkSpeed;
        if(frame>=frameCount)
            frame=1;
        sprite.setTextureRect(sf::IntRect(static_cast<int>(frame)*x,walk*y,w,l));
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {//left
        walk=3;
        if(static_cast<int>(frame)==1 || static_cast<int>(frame)==3)
            posX-=speedX;
        frame+=walkSpeed;
        if(frame>=frameCount)
            frame=1;
        sprite.setTextureRect(sf::IntRect(static_cast<int>(frame)*x,walk*y,w,l));
    }

    else
        sprite.setTextureRect(sf::IntRect(0,walk*y,w,l));
    sprite.setPosition(posX,posY);

    //bound
    screenBound();
}

void Detective::attack(Character& enemy) {
    int damage=0;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        if (weapon != nullptr) {
            damage=weapon->use(getPosition(), enemy.getPosition(), enemy.getCollisionArea(), walk);
        }

        else if(weapon->checkCollision(enemy.getPosition(), enemy.getCollisionArea(), getPosition(),collisionArea))
            damage=1;

        enemy.hit(damage);


    }
}

Detective::Detective(const Detective& original): Character(original){
    name=original.name;
    sanityPoint=original.sanityPoint;
    abilityPoint= original.abilityPoint;
}

Detective& Detective::operator =(const Detective &right) {
    if(this!=&right) {
        copier(right);
        name = right.name;
        sanityPoint = right.sanityPoint;
        abilityPoint = right.abilityPoint;
    }
    return *this;
}

void Detective::useMedicine(Medicine medication) {
    if(medication.isPsichic())
        setSanity(medication.getSanityPoint());
    else
        heal(medication.getHP());
    }

