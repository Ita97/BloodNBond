//
// Created by ita on 20/11/17.
//


#include <iostream>
#include "FireWeapon.h"
 FireWeapon::FireWeapon(fireWeaponType t): f_type(t) {
     sf::Vector2f bulletSize;

     switch(f_type){

        case fireWeaponType ::gun:
            bulletSize=sf::Vector2f(50,5);//todo finish
            ammoMax=20;
            range=sf::Vector2f(200,100/3);
            strength=10;
            description="Bella e maneggevole.";
            break;

        case fireWeaponType ::rifle:
            bulletSize=sf::Vector2f(30,6);
            ammoMax=10;
            range=sf::Vector2f(150,75/3);
            strength=20;
            description="Niente male per far saltare qualche testa!";
            break;

        case fireWeaponType ::shotGun:
            bulletSize=sf::Vector2f(25,7);
            ammoMax=5;
            range=sf::Vector2f(100,50/3);
            strength=50;
            description="Avra' effetto solo a corta distanza, ma fara' dei bel botto!";
            break;

    }
     reloadCartridge(bulletSize,ammoMax);

 }

void FireWeapon::reloadCartridge(sf::Vector2f bulletSize,int ammo){//carica l'arma
    if(ammo>ammoMax-cartridge.size())
        for(auto i=cartridge.size(); i < ammoMax; i++){
           Bullet newBullet(bulletSize);
           cartridge.push_back(newBullet);
       }
    else
        for(auto i=0; i < ammo; i++){
            Bullet newBullet(bulletSize);
            cartridge.push_back(newBullet);
        }
}



int FireWeapon:: use(sf::Vector2f detPosition, sf::Vector2f enemyPosition, sf::Vector2f collisionArea, int direction) {
    if(!cartridge.empty()){
        cartridge[cartridge.size()].setPosition(detPosition);
        cartridge[cartridge.size()].fire(6,direction,range);

        if(checkCollision(enemyPosition, collisionArea, cartridge[cartridge.size()].getPosition())){
            return strength;
        }
    }
        cartridge.pop_back();


    std::cout<<"The weapon is without ammo"<<std::endl;
}

FireWeapon* FireWeapon::clone() {
return new FireWeapon(*this);
}

void FireWeapon::Render(Window& l_window){
    cartridge[cartridge.size()].Render(l_window);
}