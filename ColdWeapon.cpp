//
// Created by ita on 20/11/17.
//

#include "ColdWeapon.h"

ColdWeapon::ColdWeapon(coldWeaponType t) : c_type(t){
    weaponClock.restart();
    ready=true;

    texture.setSmooth(true);
    switch(c_type){
        case coldWeaponType ::knife:
            name="Knife";
            range=sf::Vector2f(50,40);
            rate=sf::seconds(0.5);
            strength=5;
            texture.loadFromFile("./texture/detective/detective_knife.png");
            weaponTxt.loadFromFile(",/texture/weapon/knife.png");
            description="Potrebbe tornarmi utile..";
            textureSize=sf::Vector2i(130,170);
            frameCount=5;
            frameDistance=sf::Vector2i(132,186);
            break;
        case coldWeaponType ::sword:
            name="Sword";
            range=sf::Vector2f(60,45);
            rate=sf::seconds(0.5);
            strength=20;
            texture.loadFromFile("./texture/detective/detective_sword.png");
            weaponTxt.loadFromFile("./texture/weapon/sword.png");
            sprite.setPosition(40,40);
            sprite.scale(0.05,0.05);
            description="Bella, affilata e leggera, sarà micidiale!";
            textureSize=sf::Vector2i(170,170);
            frameCount=5;
            frameDistance=sf::Vector2i(384,185);
            break;
        case coldWeaponType ::stick:
            name="Stick";
            range=sf::Vector2f(70,50);
            rate=sf::seconds(0.5);
            strength=10;
            texture.loadFromFile("./texture/detective/detective_stick.png");
            weaponTxt.loadFromFile("./texture/weapon/pool_stick.png");

            description="";
            textureSize=sf::Vector2i(170,170);
            frameCount=6;
            frameDistance=sf::Vector2i(384,184);
            break;
    }
    sprite.setOrigin(weaponTxt.getSize().x/2,weaponTxt.getSize().y/2);
    sprite.setTexture(weaponTxt);
}
void ColdWeapon::use(){}

void ColdWeapon::startAttack(sf::Vector2f detPosition, int direction){
    position=detPosition;
    sf::Time time;
    time=weaponClock.getElapsedTime();
    if(time>rate) {
        ready = true;
        weaponClock.restart();
    }
}
ColdWeapon* ColdWeapon::clone(){
    return new ColdWeapon(*this);
}

void ColdWeapon::Render(sf::RenderWindow &l_window) {}

sf::Vector2f ColdWeapon::getCollisionArea() {
    return range;
}

sf::Vector2f ColdWeapon::getPosition() {
    return position;
}
