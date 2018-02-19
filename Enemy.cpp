//
// Created by ita on 01/11/17.
//

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "Enemy.h"
#include "FireWeapon.h"
#include "ColdWeapon.h"
#include <cmath>


Enemy::Enemy(int hp, int x, int y, int stg, EnemyType type,Behavior behavior): Character(hp, x, y),
                strength(stg), category(type),behavior(behavior){
    hit=false;
    fight=false;

    if(isSniper()){
        weapon= new FireWeapon(fireWeaponType::gun);
        range=weapon->getRange();
    }
    else if(isBerserker()){
        weapon=new ColdWeapon(coldWeaponType::sword);
        range=weapon->getRange();
    }else range=sf::Vector2f(60,60);
    switch(category) {
        case (EnemyType::dragon):
            texture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/enemy/dragon.png");//todo make texture better
            fireBall_t.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/enemy/fire_red.png");
            sprite.setTextureRect(sf::IntRect(190, 200, 190, 200));//intRect(left, top, width, length)
            sprite.setOrigin(190/2,120);
            frame = 1;
            walk=1;
            collisionArea=sf::Vector2f(100,200);
            walkingArea=sf::Vector2f(50,100);
            break;

        case (EnemyType::skeleton):
            texture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/enemy/skeleton.png");
            fireBall_t.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/enemy/fire_blue.png");
            texture.setSmooth(true);
            sprite.scale(1.6,1.6);
            sprite.setTextureRect(sf::IntRect(0,0,65,65));
            sprite.setOrigin(22,32);
            sprite.setColor(sf::Color(255,255,255,100));
            frame=0;
            walk=0;
            collisionArea=sf::Vector2f(40,60);
            walkingArea=sf::Vector2f(35,30);
            break;
    }
    fireBall.setTexture(fireBall_t);
    fireBall.setTextureRect(sf::IntRect(0,0,40,100));
    fireBall.setOrigin(20,50);
    sprite.setTexture(texture);
    sprite.setPosition(x, y);


}

void Enemy::move() {
    int frameCount=0;
    int x=0,y=0,w=0,l=0;

    switch(category) {
        case (EnemyType::dragon):
            speed.x=0.5;
            speed.y=0.35;
            x=190;
            y=200;
            w=190;
            l=200;
            walkSpeed = 0.012;
            frameCount = 3;

            break;

        case(EnemyType::skeleton):
            speed.x=0.5;
            speed.y=0.35;
            x=64;
            y=88;
            w=65;
            l=65;
            walkSpeed=0.1;
            frameCount=9;
            break;

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        walk=1;
            posX += speed.x;
        frame += walkSpeed;
        if (frame >= frameCount)
            frame = 1;
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        walk=3;
            posX -= speed.x;
        frame += walkSpeed;
        if (frame >= frameCount)
            frame = 1;

    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        walk=0;
            posY += speed.y;
        frame += walkSpeed;
        if (frame >= frameCount)
            frame = 1;
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        walk=2;
            posY -= speed.y;
        frame += walkSpeed;
        if (frame >= frameCount)
            frame = 1;
    }
    else
        frame=0;
    sprite.setTextureRect(sf::IntRect(static_cast<int>(frame) * x, walk*y, w, l));
    sprite.setPosition(posX,posY);
}

void Enemy::move(Character& character){
    int frameCount=0;
    int x=0,y=0,w=0,l=0;

    if(isBerserker()){
        speed.x=1.2;
        speed.y=0.6;
        walkSpeed=0.35;
    }
    else if(isSniper()){
        speed.x=0.8;
        speed.y=0.5;
        walkSpeed=0.25;
    }

    switch(category) {
        case (EnemyType::dragon):
            x=190;
            y=200;
            w=190;
            l=200;
            frameCount = 3;


            break;

        case(EnemyType::skeleton):
            x=64;
            y=88;
            w=65;
            l=65;
            frameCount=9;
            break;
    }

    /*Bresenham Algoritm*/

    int s,q;
    float dx,dy,d;
    dx=character.getPosX()-posX;
    dy=character.getPosY()-posY;
    float a=std::abs(dy);
    float b=std::abs(dx);
    d=2*a-b;
    if(dx>=0) q=1;
    else q=-1;
    if(dy>=0) s=1;
    else s=-1;

    if(d>0){
        //posX+=q*speed.x;
        posY+=s*speed.y;
        if(s>0)
            walk=0;
        else
            walk=2;
    } else{
        posX += q*speed.x;
        if(q>0)
            walk=1;
        else
            walk=3;

    }
    frame += walkSpeed;
    if (frame >= frameCount)
        frame = 1;
    sprite.setTextureRect(sf::IntRect(static_cast<int>(frame) * x, walk*y, w, l));
    sprite.setPosition(posX,posY);

    use();

}

bool Enemy::shootingLine(float x, float y){
    int frameCount=9;
    float dx, dy;
    dx= posX-x;
    dy= posY-y;
    if(dx<0.5 && dx>-0.5 ){
        if(dy>0)
            walk=2;
        else
            walk=0;
        return true;
    }
    if(dy<0.5 && dy>-0.5) {
        if(dx>0)
            walk=3;
        else
            walk=1;
        return true;
    }

    if(std::abs(dx)<std::abs(dy)){
        if(dx<0) {
            walk = 1;
            posX+=speed.x;
        }
        else {
            walk = 3;
            posX-=speed.x;
        }
    } else{
        if(dy<0) {
            walk = 0;
            posY+=speed.y;
        }
        else {
            walk = 2;
            posY-=speed.y;
        }
    }

    frame += walkSpeed;
    if (frame >= frameCount)
        frame = 1;
    sprite.setTextureRect(sf::IntRect(static_cast<int>(frame) * 64, walk*88, 65, 65));//TODO make it better
    sprite.setPosition(posX,posY);
    return false;

}

void Enemy::attack(Character& character){
    float attackSpeed;

    if (isSniper()){
        attackSpeed=0.1;
        if (shootingLine(character.getPosX(),character.getPosY()))
            if(!fight) {
                weapon->startAttack(getPosition(),walk);
                fireBall.setPosition(getPosition());
                fight = true;
            }
        use();
    }
    else {
        attackSpeed=0.25;
        if(!fight)
            fight=true;
    }

    if (attackFrame >= 5) {
        fight = false;
        attackFrame = 1;
    }
    if(fight) {
        attackFrame += attackSpeed;
        sprite.setTextureRect(sf::IntRect(static_cast<int>(attackFrame) * 64, walk * 88 + 88 * 4, 65, 65));

    }
}


void Enemy::Render(Window &l_window) {
    isRender=true;
    l_window.Draw(sprite);
    if(isSniper()&&fight)
        l_window.Draw(fireBall);
}

sf::Vector2f Enemy::getFeetPosition() {
    return {posX, posY+20};
}