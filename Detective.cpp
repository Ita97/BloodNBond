//
// Created by ita on 14/09/17.
//
//
// Created by ita on 14/09/17.
//
bool isHold=false;
#include <iostream>
#include "Detective.h"



Detective::Detective(const std::string& name,int h, int sp, int x, int y, Weapon* w):
        name(name), Character(h, x, y, w), sanityPoint(sp){
    level=0;
    maxHP=h;
    maxSP=sp;
    key=keyType::null;
    notebook.setWindowSize(sf::Vector2f(30, 100),780);
    notebook.setName(" Notebook");
    keychain.setWindowSize(sf::Vector2f(60, 100),810);
    keychain.setName("  Keychain");
    medikit.setWindowSize(sf::Vector2f(90, 100),840);
    medikit.setName(" Medikit");
    texture.loadFromFile("./texture/detective/detective.png");
    texture.setSmooth(true);
    if(weapon== nullptr)
        sprite.setTexture(texture);
    else
        sprite.setTexture(weapon->getTexture());
    sprite.scale(0.8,0.8);
    sprite.setOrigin(60,85);
    sprite.setPosition(x,y);
    frame=0;
    walk=0;
    attackFrame=0;
    fight=false;
    collisionArea=sf::Vector2f(40,50);
    walkingArea=sf::Vector2f(30,30);
    state_txt.loadFromFile("./texture/detective/state_bar.png");
    state_bar.setTexture(state_txt);
    state_bar.scale(0.6,0.6);
    state_bar.setPosition(0,0);
    HP.setPosition(70,25);
    HP.setSize(sf::Vector2f(115,15));
    HP.setFillColor(sf::Color(220,20,60));//cremisi, mentre bordeaux(163,0,37)
    SP.setPosition(70,45);
    SP.setSize(sf::Vector2f(115,15));
    SP.setFillColor(sf::Color(139,25,155));//purple

    void_star.loadFromFile("./texture/detective/void_star.png");
    void_star.setSmooth(true);
    blue_star.loadFromFile("./texture/detective/blue_star.png");
    blue_star.setSmooth(true);
    red_star.loadFromFile("./texture/detective/red_star.png");
    yellow_star.loadFromFile("./texture/detective/yellow_star.png");
    yellow_star.setSmooth(true);
    star1.setTexture(void_star);
    star1.setOrigin(void_star.getSize().x/2,void_star.getSize().y/2);
    star1.setScale(0.04,0.04);
    star1.setPosition(740,50);
    star2.setTexture(void_star);
    star2.setOrigin(star1.getOrigin());
    star2.setScale(0.04,0.04);
    star2.setPosition(820,50);
    star3.setTexture(void_star);
    star3.setOrigin(star1.getOrigin());
    star3.setScale(0.04,0.04);
    star3.setPosition(900,50);
}


void Detective::move() {

    float walkSpeed=0.17;
    int frameCount=9;
    float speedX=1.3, speedY=1;
    int x=129, y=183, w=120, l=170;


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { //down
        walk = 0;
        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            posY += speedY;
            frame += walkSpeed;
        }
        if (frame >= frameCount)
            frame = 1;
        sprite.setTextureRect(sf::IntRect(static_cast<int>(frame) * x, walk * y, w, l));
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { //right
        walk = 1;
        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            posX += speedX;
            frame += walkSpeed;
        }
        if (frame >= frameCount)
            frame = 1;
        sprite.setTextureRect(sf::IntRect(static_cast<int>(frame) * x, walk * y, w, l));
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { //up
        walk = 2;
        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            posY -= speedY;
            frame += walkSpeed;
        }
        if (frame >= frameCount)
            frame = 1;
        sprite.setTextureRect(sf::IntRect(static_cast<int>(frame) * x, walk * y, w, l));
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {//left
        walk = 3;
        if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
            posX -= speedX;
            frame += walkSpeed;
        }
        if (frame >= frameCount)
            frame = 1;
        sprite.setTextureRect(sf::IntRect(static_cast<int>(frame) * x, walk * y, w, l));
    } else {
        sprite.setTextureRect(sf::IntRect(0, walk * y, w, l)); //reset stand position
    }
        sprite.setPosition(posX, posY);

    //bound

}


void Detective::attack() {
    sf::Vector2i size(120,170),distance(129,185);
    float attackSpeed=0.15;
    int frameCount=5;
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
        fight = true;
    }
    if (weapon != nullptr) {
        if(fight&&attackFrame>3&&attackFrame<4)
            weapon->startAttack(getPosition(),walk);
        weapon->use();
        weapon->getTextureDetails(size,distance,frameCount);
    }
    if (attackFrame >= frameCount) {
        fight = false;
        attackFrame = 1;
    }
    if(fight) {
        attackFrame += attackSpeed;
        sprite.setTextureRect(sf::IntRect(static_cast<int>(attackFrame) * distance.x, walk * distance.y + distance.y * 4, size.x, size.y));

    }
}

void Detective::useInventory(sf::RenderWindow& window) {
        medikit.SelectObject(sf::Mouse::getPosition(window));
        if (medikit.objectIsUsed()){
            useMedicine(*medikit.getObject());
            medikit.throwElement(medikit.getObjectPosition());
        }
        notebook.SelectObject(sf::Mouse::getPosition(window));
        if (notebook.objectIsUsed()){
            notebook.getObject()->open();
            notebook.update();
        }
        keychain.SelectObject(sf::Mouse::getPosition(window));
        if (keychain.objectIsUsed()){
            key = keychain.getObject()->getMaterial();
            keychain.getObject()->use();
        }
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


void Detective::interact(Obstacle *obs) {
    obs->unlock(key);
}

//Rendering

void Detective::Render(sf::RenderWindow& l_window){
    isRender=true;
    l_window.draw(sprite);
    if(weapon!=nullptr)
        weapon->Render(l_window);
}

void Detective::RenderInventory(sf::RenderWindow& l_window){
    l_window.draw(HP);
    l_window.draw(SP);
    l_window.draw(state_bar);
    if(weapon!=nullptr)
        l_window.draw(weapon->getSprite());
    medikit.Render(l_window);
    keychain.Render(l_window);
    notebook.Render(l_window);
    l_window.draw(star1);
    l_window.draw(star2);
    l_window.draw(star3);
}

sf::Vector2f Detective::getFeetPosition() {
    return {posX, posY+20};
}
