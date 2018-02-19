//
// Created by ita on 20/11/17.
//

#include "ColdWeapon.h"

ColdWeapon::ColdWeapon(coldWeaponType t) : c_type(t){
    weaponClock.restart();
    hit=false;

    texture.setSmooth(true);
    switch(c_type){
        case coldWeaponType ::knife:
            name="Knife";
            range=sf::Vector2f(40,110/3);
            rate=sf::seconds(0.5);
            strength=5;
            texture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/detective/detective_knife.png");
            description="Potrebbe tornarmi utile..";
            textureSize=sf::Vector2i(130,170);
            frameCount=6;
            frameDistance=sf::Vector2i(132,186);
            break;
        case coldWeaponType ::sword:
            name="Sword";
            range=sf::Vector2f(53,120/3);
            rate=sf::seconds(0.5);
            strength=20;
            texture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/detective/detective_sword.png");
            description="Bella, affilata e leggera, sarà micidiale!";
            textureSize=sf::Vector2i(170,170);
            frameCount=6;
            frameDistance=sf::Vector2i(384,185);
            break;
        case coldWeaponType ::stick:
            name="Stick";
            range=sf::Vector2f(60,130/3);
            rate=sf::seconds(0.5);
            strength=10;
            texture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/detective/detective_stick.png");
            description="";
            textureSize=sf::Vector2i(170,170);
            frameCount=6;
            frameDistance=sf::Vector2i(384,184);
            break;
    }
}
void ColdWeapon::use(){}

int ColdWeapon::startAttack(sf::Vector2f detPosition, int direction){
    position=detPosition;
    sf::Time time;
    time=weaponClock.getElapsedTime();
    if(time>rate)
        weaponClock.restart();
    return 0;
}
ColdWeapon* ColdWeapon::clone(){
    return new ColdWeapon(*this);
}

void ColdWeapon::Render(Window &l_window) {}

sf::Vector2f ColdWeapon::getCollisionArea() {
    return range;
}

sf::Vector2f ColdWeapon::getPosition() {
    return position;
}