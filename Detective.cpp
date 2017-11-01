//
// Created by ita on 14/09/17.
//

#include "Detective.h"
#include <SFML/Graphics.hpp>

Detective::Detective(int h, int x, int y, Weapon* w, std::string name, int sp, int ap):
        Character(h, x, y, w), name(name), sanityPoint(sp), abilityPoint(ap){

    sf::Texture t_det;
    t_det.loadFromFile("/home/ita/CLionProjects/BloodBond/pic/sprite/first-detective.png"); //todo trova sprite adatto
    sf::Sprite det(t_det);
    Detective::detective=det;
    detective.setTextureRect(sf::IntRect(190,250,190,150));
    detective.setPosition(0,0);
}

void Detective::move(int x, int y) {

    float frame=1;
    float walkSpeed=0.12;
    int frameCount=3;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        x+=2;
        frame+=walkSpeed;
        if(frame>=frameCount)
            frame=0;
        detective.setTextureRect(sf::IntRect(static_cast<int>(frame)*190,445,190,150));
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {//TODO resolve left walk bug
        x-=2;
        frame+=walkSpeed;
        if(frame>=frameCount)
            frame=0;
        detective.setTextureRect(sf::IntRect(5+static_cast<int>(frame)*190,250,190,150));
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  {
        y+=0.75;
        frame+=walkSpeed;
        if(frame>=frameCount)
            frame=0;
        detective.setTextureRect(sf::IntRect(static_cast<int>(frame)*190,0,190,200));
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        y-=0.75;
        frame+=walkSpeed;
        if(frame>=frameCount)
            frame=0;
        detective.setTextureRect(sf::IntRect(static_cast<int>(frame)*190,620,190,200));
    }
    detective.setPosition(x,y);
}

void Detective::attack() {}

/*void Detective::use(Tools *t) {
    t->useTool();
    }

*/