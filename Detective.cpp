//
// Created by ita on 14/09/17.
//

#include <iostream>
#include "Detective.h"


Detective::Detective(const std::string& name,int h, int sp, int ap, int x, int y, Weapon* w):
        name(name), Character(h, x, y, w), sanityPoint(sp), abilityPoint(ap){
    t_det.loadFromFile("/home/ita/CLionProjects/BloodBond/pic/sprite/first-detective.png");
    detective.setTexture(t_det);
    detective.setTextureRect(sf::IntRect(0,0,85,110)); //left, top, width, length
    detective.setPosition(0,0);
    frame=0;
}

void Detective::move() {

    float walkSpeed=0.015;
    int frameCount=5;
    float x=0.72, y=0.42;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { //right
        if(static_cast<int>(frame)==1 || static_cast<int>(frame)==3)
            posX+=x;
        frame+=walkSpeed;
        if(frame>=frameCount)
            frame=1;
        detective.setTextureRect(sf::IntRect(static_cast<int>(frame)*69,103,73,110));
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {//left
        if(static_cast<int>(frame)==1 || static_cast<int>(frame)==3)
            posX-=x;
        frame+=walkSpeed;
        if(frame>=frameCount)
            frame=1;
        detective.setTextureRect(sf::IntRect(static_cast<int>(frame)*69,309,73,110));
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))  { //down
        if(static_cast<int>(frame)==1 || static_cast<int>(frame)==3)
            posY+=y;
        frame+=walkSpeed;
        if(frame>=frameCount)
            frame=1;
        detective.setTextureRect(sf::IntRect(static_cast<int>(frame)*69,0,69,110));
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){ //up
        if(static_cast<int>(frame)==1 || static_cast<int>(frame)==3)
            posY-=y;
        frame+=walkSpeed;
        if(frame>=frameCount)
            frame=1;
        detective.setTextureRect(sf::IntRect(static_cast<int>(frame)*68,206,68,110));
    }
    detective.setPosition(posX,posY);

    //bound
    if(posX<=-20) posX=-20;
    if(posX>=900) posX=900;
    if(posY<=-20) posY=-20;
    if(posY>=380) posY=380;
}

void Detective::attack(Character& enemy) {
    int damage=1;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        if ((posX < enemy.getPosX())&&(enemy.getPosX() - posX < 50) || (posX>enemy.getPosX())&& (posX - enemy.getPosX() < 100)){
            if((posY>=enemy.getPosY())&&(posY - enemy.getPosY() < 100) || (posY<enemy.getPosY())&&(enemy.getPosY() - posY < 30)){
            if (weapon != nullptr)
                damage = weapon->getStrength();
            enemy.setHp(-damage);
            }
        }
        else
                std::cout<<"Dodge"<<std::endl;
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
void Detective::use(Medicine medication) {
    if(medication.isPsichic())
        setSanity(medication.getSanityPoint());
    else
        setHp(medication.getHealingPoint());
    }


void Detective::Render(Window &l_window) {
    l_window.Draw(detective);
}