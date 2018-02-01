//
// Created by ita on 14/09/17.
//
bool isHold=false;
#include <iostream>
#include "Detective.h"



Detective::Detective(const std::string& name,int h, int sp, int ap, int x, int y, Weapon* w):
        name(name), Character(h, x, y, w), sanityPoint(sp), abilityPoint(ap){
    notebook.setWindowSize(sf::Vector2f(30, 100),780);
    notebook.setName(" Notebook");
    keychain.setWindowSize(sf::Vector2f(60, 100),810);
    keychain.setName("  Keychain");
    medikit.setWindowSize(sf::Vector2f(90, 100),840);
    medikit.setName(" Medikit");
    torch=false;
    texture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/detective/first_hero.png");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0,0,73,110)); //left, top, width, length
    sprite.setOrigin(73/2,110/2);
    sprite.setPosition(x,y);
    frame=0;
    walk=0;
    collisionArea=sf::Vector2f(40,110/3);
}


void Detective::move() {

    float walkSpeed=0.015;
    int frameCount=5;
    float speedX=0.62, speedY=0.32;
    int x=69, y=103, w=73, l=110;


    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))  { //down
        walk=0;
        if(static_cast<int>(frame)==1 || static_cast<int>(frame)==3)
            posY+=speedY;
        frame+=walkSpeed;
        if(frame>=frameCount)
            frame=1;
        sprite.setTextureRect(sf::IntRect(static_cast<int>(frame)*x,walk*y,w,l));
    }

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) { //right
        walk=1;
        if(static_cast<int>(frame)==1 || static_cast<int>(frame)==3)
            posX+=speedX;
        frame+=walkSpeed;
        if(frame>=frameCount)
            frame=1;
        sprite.setTextureRect(sf::IntRect(static_cast<int>(frame)*x,walk*y,w,l));
    }

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){ //up
        walk=2;
        if(static_cast<int>(frame)==1 || static_cast<int>(frame)==3)
            posY-=speedY;
        frame+=walkSpeed;
        if(frame>=frameCount)
            frame=1;
        sprite.setTextureRect(sf::IntRect(static_cast<int>(frame)*x,walk*y,w,l));
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {//left
        walk=3;
        if(static_cast<int>(frame)==1 || static_cast<int>(frame)==3)
            posX-=speedX;
        frame+=walkSpeed;
        if(frame>=frameCount)
            frame=1;
        sprite.setTextureRect(sf::IntRect(static_cast<int>(frame)*x,walk*y,w,l));
    }

    else
        sprite.setTextureRect(sf::IntRect(0,walk*y,w,l));
    sprite.setPosition(posX,posY);

    //bound
    screenBound();
}

void Detective::attack(Character& enemy) {
    int damage=0;
        if (weapon != nullptr) {
            damage = weapon->use(getPosition(), enemy.getPosition(), enemy.getCollisionArea(), walk);
        } else if (weapon->checkCollision(enemy.getPosition(), enemy.getCollisionArea(), getPosition(), collisionArea))
            damage = 1;

        enemy.hit(damage);

}

void Detective::use(Window& window) {
    //interazioni con le inventories mediante mouse e tastiera
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::M)){
        if(!isHold) {

            if (!medikit.isOpen()) {
                openMedikit();
                closeNotebook();
                closeKeychain();
            }
            else
                closeMedikit();
        }
        isHold=true;
    }

    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::K)) {
        if (!isHold) {
            if (!keychain.isOpen()) {
                openKeychain();
                closeNotebook();
                closeMedikit();
                }
            else
                closeKeychain();
        }
        isHold=true;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::N)){
        if(!isHold) {
            if (!notebook.isOpen()) {
                openNotebook();
                closeMedikit();
                closeKeychain();
            }
            else
                closeNotebook();
        }
        isHold=true;
    }
    else if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        if(!isHold){
            if(weapon->checkCollision(medikit.getPosition(),medikit.getCollisionArea(),
                                      sf::Vector2f(sf::Mouse::getPosition(window.getWindow()).x,sf::Mouse::getPosition(window.getWindow()).y))){
                if (!medikit.isOpen()&&!keychain.isOpen()&&!notebook.isOpen())
                    openMedikit();
                else
                    closeMedikit();
            }else if(weapon->checkCollision(keychain.getPosition(),keychain.getCollisionArea(),
                                            sf::Vector2f(sf::Mouse::getPosition(window.getWindow()).x,sf::Mouse::getPosition(window.getWindow()).y))){
                    if (!keychain.isOpen()&&!notebook.isOpen()) {
                        openKeychain();
                        closeNotebook();
                        closeMedikit();
                    }
                    else
                        closeKeychain();
            }else if(weapon->checkCollision(notebook.getPosition(),notebook.getCollisionArea(),
                                            sf::Vector2f(sf::Mouse::getPosition(window.getWindow()).x,sf::Mouse::getPosition(window.getWindow()).y))){
                if (!notebook.isOpen()) {
                    openNotebook();
                    closeMedikit();
                    closeKeychain();
                }
                else
                    closeNotebook();
            }else {

                medikit.SelectObject(sf::Mouse::getPosition(window.getWindow()));
                if(medikit.objectIsUsed()){
                    useMedicine(*medikit.getObject());
                    medikit.throwElement(medikit.getObjectPosition());
                }
                notebook.SelectObject(sf::Mouse::getPosition(window.getWindow()));
                if(notebook.objectIsUsed()){
                    notebook.getObject()->open();
                    notebook.update();
                }
                keychain.SelectObject(sf::Mouse::getPosition(window.getWindow()));
                if(keychain.objectIsUsed())
                    keychain.getObject()->use();


            }
        }
        isHold=true;
    }
    else
        isHold=false;



}

Detective::Detective(const Detective& original): Character(original){
    name=original.name;
    sanityPoint=original.sanityPoint;
    abilityPoint= original.abilityPoint;
}

Detective& Detective::operator =(const Detective &right) {
    if(this!=&right) {
        copier(right);
        name = right.name;
        sanityPoint = right.sanityPoint;
        abilityPoint = right.abilityPoint;
    }
    return *this;
}

void Detective::useMedicine(Medicine& medication) {
    if(medication.isPsichic())
        setSanity(medication.getSanityPoint());
    else
        heal(medication.getHP());
    }

void Detective::Render(Window& l_window){
    l_window.Draw(sprite);
    weapon->Render(l_window);
}

void Detective::getMedicine(Medicine &med) {
    bool isNotFull;
        isNotFull=medikit.getElement(med);
    if(!isNotFull)
        std::cout<<"Non puoi portarla con te";
}

void Detective::getMessage(Message &note) {
    bool isNotFull;
    isNotFull=notebook.getElement(note);
    if(!isNotFull)
        std::cout<<"Non puoi portarlo con te";
}

void Detective::getKey(Key &key) {
    bool isNotFull;
    isNotFull=keychain.getElement(key);
    if(!isNotFull)
        std::cout<<"Non puoi portarla con te";
}

void Detective::RenderInventory(Window& l_window){
    medikit.Render(l_window);
    keychain.Render(l_window);
    notebook.Render(l_window);

}