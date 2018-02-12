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
     texture.setSmooth(true);
     switch(f_type){

        case fireWeaponType ::gun:
             name="Gun";
             bulletSize=sf::Vector2f(15,4);
             ammoMax=20;
             range=sf::Vector2f(400,300/2);
             strength=10;
             shotSpeed=11;
             texture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/detective/detective_gun.png");
             description="Bella e maneggevole.";
             textureSize=sf::Vector2i(130,170);
             frameCount=6;
             frameDistance=sf::Vector2i(129,183);
             break;

        case fireWeaponType ::rifle:
             name="Rifle";
             bulletSize=sf::Vector2f(15,5);
             ammoMax=10;
             range=sf::Vector2f(300,200/2);
             strength=20;
             shotSpeed=10;
             texture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/detective/detective_rifle.png");
             description="Niente male per far saltare qualche testa!";
             textureSize=sf::Vector2i(130,170);
             frameCount=8;
             frameDistance=sf::Vector2i(128,182);
             break;

        case fireWeaponType ::shotGun:
             name="Shotgun";
             bulletSize=sf::Vector2f(15,6);
             ammoMax=5;
             range=sf::Vector2f(200,100/2);
             strength=50;
             shotSpeed=9;
             texture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/detective/detective_rifle.png");
             description="Avra' effetto solo a corta distanza, ma fara' dei bei botti!";
             textureSize=sf::Vector2i(130,170);
             frameCount=8;
             frameDistance=sf::Vector2i(128,182);
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

int FireWeapon::use(sf::Vector2f detPosition, int direction){
    sf::Time time;
    time=weaponClock.getElapsedTime();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && time>rate) {
        hit=false;
        if (cartridge > 0) {
            bullet.setPosition(detPosition);
            cartridge--;

        } else
            std::cout << "The weapon is without ammo" << std::endl;
        weaponClock.restart();
    }
    if (isInsideRange(detPosition, bullet.getPosition()))
        bullet.fire(shotSpeed, direction);
    else
        bullet.setPosition(sf::Vector2f(-1000,-1000));
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

sf::Vector2f FireWeapon::getCollisionArea() {
    return bullet.getSize();
}

sf::Vector2f FireWeapon::getPosition() {
    return bullet.getPosition();
}