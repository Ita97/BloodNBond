//
// Created by ita on 20/11/17.
//

#include "ColdWeapon.h"

ColdWeapon::ColdWeapon(coldWeaponType t) : c_type(t){

    range=sf::Vector2f(40,110/3);
    switch(c_type){
        case coldWeaponType ::knife:
            strength=5;
            description="Potrebbe tornarmi utile..";
            break;
        case coldWeaponType ::axe:
            strength=30;
            description="E' pesante, ma non e' niente male";
            break;
        case coldWeaponType ::stick:
            strength=10;
            description="";
            break;

    }
}

int ColdWeapon::use(sf::Vector2f detPosition, sf::Vector2f enemyPosition, sf::Vector2f collisionArea, int direction) {
    if(checkCollision(enemyPosition, collisionArea, detPosition, range)){
        return strength;
    }



}

ColdWeapon* ColdWeapon::clone(){
    return new ColdWeapon(*this);
}

void ColdWeapon::Render(Window &l_window) {}