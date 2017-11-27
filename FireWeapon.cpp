//
// Created by ita on 20/11/17.
//


#include <iostream>
#include "FireWeapon.h"
 FireWeapon::FireWeapon(fireWeaponType t): f_type(t) {
     sf::Vector2f bulletSize;

     switch(f_type){

        case fireWeaponType ::gun:
            bulletSize=sf::Vector2f(3,3);//todo finish
            ammoMax=30;
            range=sf::Vector2f(200,200/3);
            strength=10;
            description="Bella e maneggevole.";
            break;

        case fireWeaponType ::rifle:
            bulletSize=sf::Vector2f(5,5);
            ammoMax=10;
            range=sf::Vector2f(150,75/3);
            strength=20;
            description="Niente male per far saltare qualche testa!";
            break;

        case fireWeaponType ::shotGun:
            bulletSize=sf::Vector2f(7,7);
            ammoMax=5;
            range=sf::Vector2f(100,50/3);
            strength=50;
            description="Avra' effetto solo a corta distanza, ma fara' dei bei botti!";
            break;

    }

    reloadCartridge(bulletSize,ammoMax);
 }

void FireWeapon::reloadCartridge(sf::Vector2f bulletSize, int ammo) {
    bullet.setSize(bulletSize);
    cartridge=ammo;
}
int FireWeapon::use(sf::Vector2f detPosition, sf::Vector2f enemyPosition, sf::Vector2f collisionArea, int direction) {
    if(cartridge!=0) {
        bullet.setPosition(detPosition);
        for(int i=0; i<range.x;i++) {
            bullet.fire(6, direction);
            if (checkCollision(enemyPosition, collisionArea, bullet.getPosition()))
                return strength;
        cartridge--;
        }

    }
    else
        std::cout<<"The weapon is without ammo"<<std::endl;

    return 0;
}

FireWeapon* FireWeapon::clone() {
return new FireWeapon(*this);
}

void FireWeapon::Render(Window& l_window){
    bullet.Render(l_window);
}