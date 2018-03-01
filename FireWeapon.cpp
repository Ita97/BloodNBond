//
// Created by ita on 20/11/17.
//

#include <SFML/System/Vector2.hpp>
#include <iostream>
#include "FireWeapon.h"
 FireWeapon::FireWeapon(fireWeaponType t): f_type(t) {
     num=0;
     cartridge=0;
     rate=sf::seconds(0.5);
     weaponClock.restart();
     ready=true;
     texture.setSmooth(true);
     switch(f_type){

        case fireWeaponType ::gun:
             name="Gun";
             bulletSize=sf::Vector2f(15,4);
             ammoMax=20;
             range=sf::Vector2f(400,300/2);
             strength=10;
             shotSpeed=11;
             texture.loadFromFile("./texture/detective/detective_gun.png");
             weaponTxt.loadFromFile("./texture/weapon/revolver.png");
             description="Bella e maneggevole.";
             textureSize=sf::Vector2i(130,170);
             frameCount=5;
             frameDistance=sf::Vector2i(129,183);
             sprite.scale(0.25,0.28);
             sprite.setPosition(38,40);
             break;

        case fireWeaponType ::rifle:
             name="Rifle";
             bulletSize=sf::Vector2f(15,5);
             ammoMax=10;
             range=sf::Vector2f(300,200/2);
             strength=20;
             shotSpeed=10;
             texture.loadFromFile("./texture/detective/detective_rifle.png");
             weaponTxt.loadFromFile("./texture/weapon/rifle.png");
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
             texture.loadFromFile("./texture/detective/detective_rifle.png");
             weaponTxt.loadFromFile("./texture/weapon/shotgun.png");
             description="Avra' effetto solo a corta distanza, ma fara' dei bei botti!";
             textureSize=sf::Vector2i(130,170);
             frameCount=8;
             frameDistance=sf::Vector2i(128,182);
             break;

    }
     reloadCartridge(ammoMax);
     sprite.setOrigin(weaponTxt.getSize().x/2,weaponTxt.getSize().y/2);
     sprite.setTexture(weaponTxt);
 }

void FireWeapon::reloadCartridge(int ammo) {
    if(ammo>=ammoMax-cartridge)
        cartridge=ammoMax;

    else
        cartridge+=ammo;
}


void FireWeapon::use(){
    auto pos=shotBullets.cbegin();
    for(auto i:shotBullets){

        if (isInsideRange(i->getBeginningPos(), i->getPosition()))
            i->fire(shotSpeed);
        else
            shotBullets.erase(pos);
        pos++;
    }
}

void FireWeapon::startAttack(sf::Vector2f detPosition, int direction){
    sf::Time time;
    time=weaponClock.getElapsedTime();
    if(time>rate) {
        ready=true;
        if (cartridge > 0) {
            bullet=new Bullet(direction,detPosition);
            bullet->setSize(bulletSize);
            shotBullets.push_back(bullet);
            cartridge--;

        }
        weaponClock.restart();
    }
    auto pos=shotBullets.cbegin();
    for(auto i:shotBullets){

        if (isInsideRange(detPosition, i->getPosition()))
            i->fire(shotSpeed);
        else
            shotBullets.erase(pos);
        pos++;
    }
}

FireWeapon* FireWeapon::clone() {
return new FireWeapon(*this);
}

void FireWeapon::Render(sf::RenderWindow &l_window) {
    for(auto i:shotBullets)
        i->Render(l_window);
}

bool FireWeapon::isInsideRange(sf::Vector2f focus, sf::Vector2f target) {
     return checkCollision(focus,range,target); //*
}
/* E' uguale a scrivere:
    if(target.x>focus.x-range.x && target.x<focus.x+range.x)  //bound x
        if(target.y>focus.y-range.y && target.y<focus.y+range.y) //bound y*/

sf::Vector2f FireWeapon::getCollisionArea() {
    return bulletSize;
}

sf::Vector2f FireWeapon::getPosition() {
    num++;
    if(!shotBullets.empty()) {
        if (num >= shotBullets.size())
            num = 0;
        return shotBullets[num]->getPosition();
    }
}#include <iostream>
#include "FireWeapon.h"
 FireWeapon::FireWeapon(fireWeaponType t): f_type(t) {
     num=0;
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
     reloadCartridge(ammoMax);
 }

void FireWeapon::reloadCartridge(int ammo) {
    if(ammo>=ammoMax-cartridge)
        cartridge=ammoMax;

    else
        cartridge+=ammo;
}


void FireWeapon::use(){
    auto pos=shotBullets.cbegin();
    for(auto i:shotBullets){

        if (isInsideRange(i->getBeginningPos(), i->getPosition()))
            i->fire(shotSpeed);
        else
            shotBullets.erase(pos);
        pos++;
    }
}

int FireWeapon::startAttack(sf::Vector2f detPosition, int direction){
    sf::Time time;
    time=weaponClock.getElapsedTime();
    if(time>rate) {
        if (cartridge > 0) {
            bullet=new Bullet(direction,detPosition);
            bullet->setSize(bulletSize);
            shotBullets.push_back(bullet);
            cartridge--;

        } else
            std::cout << "The weapon is without ammo" << std::endl;
        weaponClock.restart();
    }
    auto pos=shotBullets.cbegin();
    for(auto i:shotBullets){

        if (isInsideRange(detPosition, i->getPosition()))
            i->fire(shotSpeed);
        else
            shotBullets.erase(pos);
        pos++;
    }
    return 0;
}

FireWeapon* FireWeapon::clone() {
return new FireWeapon(*this);
}

void FireWeapon::Render(Window &l_window) {
    for(auto i:shotBullets)
        i->Render(l_window);
}

bool FireWeapon::isInsideRange(sf::Vector2f focus, sf::Vector2f target) {
     return checkCollision(focus,range,target); //*
}
/* E' uguale a scrivere:
    if(target.x>focus.x-range.x && target.x<focus.x+range.x)  //bound x
        if(target.y>focus.y-range.y && target.y<focus.y+range.y) //bound y*/

sf::Vector2f FireWeapon::getCollisionArea() {
    return bulletSize;
}

sf::Vector2f FireWeapon::getPosition() {
    num++;
    if(!shotBullets.empty()) {
        if (num >= shotBullets.size())
            num = 0;
        return shotBullets[num]->getPosition();
    }
}
