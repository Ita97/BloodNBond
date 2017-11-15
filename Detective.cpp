//
// Created by ita on 14/09/17.
//

#include "Detective.h"


Detective::Detective(int h, int x, int y, Weapon* w, std::string name, int sp, int ap):
        Character(h, x, y, w), name(name), sanityPoint(sp), abilityPoint(ap){
    t_det.loadFromFile("/home/ita/CLionProjects/BloodBond/pic/sprite/first-detective.png"); //todo trova sprite adatto
    detective.setTexture(t_det);
    detective.setTextureRect(sf::IntRect(0,0,85,110)); //left, top, width, length
    detective.setPosition(0,0);
}

void Detective::move() {

    float walkSpeed=0.015;
    int frameCount=5;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { //right
        if(static_cast<int>(frame)==1 || static_cast<int>(frame)==3)
            posX+=0.42;
        frame+=walkSpeed;
        if(frame>=frameCount)
            frame=1;
        detective.setTextureRect(sf::IntRect(static_cast<int>(frame)*70,103,73,110));
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {//left
        if(static_cast<int>(frame)==1 || static_cast<int>(frame)==3)
        posX-=0.42;
        frame+=walkSpeed;
        if(frame>=frameCount)
            frame=1;
        detective.setTextureRect(sf::IntRect(static_cast<int>(frame)*70,309,73,110));
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))  { //down
        if(static_cast<int>(frame)==1 || static_cast<int>(frame)==3)
        posY+=0.22;
        frame+=walkSpeed;
        if(frame>=frameCount)
            frame=1;
        detective.setTextureRect(sf::IntRect(static_cast<int>(frame)*69,0,69,110));
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){ //up
        if(static_cast<int>(frame)==1 || static_cast<int>(frame)==3)
        posY-=0.22;
        frame+=walkSpeed;
        if(frame>=frameCount)
            frame=1;
        detective.setTextureRect(sf::IntRect(static_cast<int>(frame)*68,206,68,110));
    }
    detective.setPosition(posX,posY);
}

void Detective::attack() {}

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