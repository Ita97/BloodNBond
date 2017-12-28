//
// Created by ita on 20/11/17.
//

#include "ColdWeapon.h"

ColdWeapon::ColdWeapon(coldWeaponType t) : c_type(t){
    weaponClock.restart();
    range=sf::Vector2f(40,110/3);
    switch(c_type){
        case coldWeaponType ::knife:
            name="Knife";
            rate=sf::seconds(0.0015);
            strength=5;
            description="Potrebbe tornarmi utile..";
            break;
        case coldWeaponType ::axe:
            name="Axe";
            rate=sf::seconds(0.0002);
            strength=30;
            description="E' pesante, ma non e' niente male";
            break;
        case coldWeaponType ::stick:
            name="Stick";
            rate=sf::seconds(0.005);
            strength=10;
            description="";
            break;

    }
}

int ColdWeapon::use(sf::Vector2f detPosition, sf::Vector2f enemyPosition, sf::Vector2f collisionArea, int direction) {
    sf::Time time;
    time=weaponClock.getElapsedTime();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&time>rate) {
        if (checkCollision(enemyPosition, collisionArea, detPosition, range)) {
            return strength;
        }
        weaponClock.restart();
    }
}

ColdWeapon* ColdWeapon::clone(){
    return new ColdWeapon(*this);
}

void ColdWeapon::Render(Window &l_window) {
    //todo add attack-sprite
}