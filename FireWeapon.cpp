#include <SFML/System/Vector2.hpp>

//
// Created by ita on 20/11/17.
//

#include <iostream>
#include "FireWeapon.h"
 FireWeapon::FireWeapon(fireWeaponType t): f_type(t) {
     sf::Vector2f bulletSize;
     cartridge=0;
     rate=sf::seconds(0.5);
     weaponClock.restart();
     hit=false;
     switch(f_type){

        case fireWeaponType ::gun:
             name="Gun";
             bulletSize=sf::Vector2f(15,3);//todo finish
             ammoMax=20;
             range=sf::Vector2f(300,200/2);
             strength=10;
             shotSpeed=11;
             description="Bella e maneggevole.";
             break;

        case fireWeaponType ::rifle:
             name="Rifle";
             bulletSize=sf::Vector2f(15,4);
             ammoMax=10;
             range=sf::Vector2f(150,90/2);
             strength=20;
             shotSpeed=10;
             description="Niente male per far saltare qualche testa!";
             break;

        case fireWeaponType ::shotGun:
             name="Shotgun";
             bulletSize=sf::Vector2f(15,5);
             ammoMax=5;
             range=sf::Vector2f(100,60/2);
             strength=50;
             shotSpeed=9;
             description="Avra' effetto solo a corta distanza, ma fara' dei bei botti!";
             break;

    }

    reloadCartridge(bulletSize,ammoMax);
 }

void FireWeapon::reloadCartridge(sf::Vector2f bulletSize, int ammo) {
    bullet.setSize(bulletSize);

    if(ammo>=ammoMax-cartridge)
        cartridge=ammoMax;

    else
        cartridge+=ammo;
}

int FireWeapon::use(sf::Vector2f detPosition, sf::Vector2f enemyPosition, sf::Vector2f collisionArea, int direction) { //todo correct speed bug and the rendering
    sf::Time time;
    time=weaponClock.getElapsedTime();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && time>rate) {
        hit=false;
        if (cartridge > 0) {
            bullet.setPosition(detPosition);
            cartridge--;

        } else
            std::cout << "The weapon is without ammo" << std::endl;
        weaponClock.restart();
    }
    if (isInsideRange(detPosition, bullet.getPosition())) {
        bullet.fire(shotSpeed, direction);
        if (!hit && checkCollision(enemyPosition, collisionArea, bullet.getPosition())){
            hit=true;
            return strength;
        }
    }
    else
        bullet.setPosition(sf::Vector2f(100000,100000));//todo find a way to delete it
    return 0;
}

FireWeapon* FireWeapon::clone() {
return new FireWeapon(*this);
}

void FireWeapon::Render(Window &l_window) {
   bullet.Render(l_window);
}

bool FireWeapon::isInsideRange(sf::Vector2f focus, sf::Vector2f target) {
     return checkCollision(focus,range,target); //*
}
/* E' uguale a scrivere:
    if(target.x>focus.x-range.x && target.x<focus.x+range.x)  //bound x
        if(target.y>focus.y-range.y && target.y<focus.y+range.y) //bound y*/