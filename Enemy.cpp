//
// Created by ita on 01/11/17.
//

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "Enemy.h"
#include "Detective.h"


Enemy::Enemy(int hp, int x, int y, int stg, Weapon *weapon, EnemyType type): Character(hp, x, y, weapon), strength(stg), category(type){
    hit=false;
    switch(category) {
        case (EnemyType::dragon):
            texture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/enemy/dragon.png");
            sprite.setTextureRect(sf::IntRect(190, 200, 190, 200));//intRect(left, top, width, length)
            sprite.setOrigin(190/2,120);
            frame = 1;
            walk=1;
            collisionArea=sf::Vector2f(100,600);
            break;

        case (EnemyType::skeleton):
            texture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/enemy/skeleton.png");
            texture.setSmooth(true);
            sprite.scale(1.6,1.6);
            sprite.setTextureRect(sf::IntRect(0,0,65,65));
            sprite.setOrigin(32,40);
            frame=0;
            walk=0;
            collisionArea=sf::Vector2f(40,40);
            break;
    }
    sprite.setTexture(texture);
    sprite.setPosition(x, y);


}

void Enemy::move() {
    float walkSpeed=0;
    int frameCount=0;
    int x=0,y=0,w=0,l=0;
    float speedX=0,speedY=0;

    switch(category) {
        case (EnemyType::dragon):
            speedX=0.5;
            speedY=0.35;
            x=190;
            y=200;
            w=190;
            l=200;
            walkSpeed = 0.012;
            frameCount = 3;

            //bound enemy in the window

            break;

        case(EnemyType::skeleton):
            break; //TODO complete

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        walk=2;
        if (static_cast<int>(frame) != 1)
            posX += speedX;
        frame += walkSpeed;
        if (frame >= frameCount)
            frame = 0;
        sprite.setTextureRect(sf::IntRect(static_cast<int>(frame) * x, walk*y, w, l));//390
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        walk=1;
        int l_frame=0;
        if (static_cast<int>(frame) != 1)
            posX -= speedX;
        frame += walkSpeed;
        if (frame >= 3)
            frame = 0;
        //riordino dei passi
        if (static_cast<int>(frame) == 0) l_frame = 2;
        if (static_cast<int>(frame) == 1) l_frame = 1;
        if (static_cast<int>(frame) == 2) l_frame = 0;

        sprite.setTextureRect(sf::IntRect(l_frame * x, walk*y, w, l));//200

    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        walk=0;
        if (static_cast<int>(frame) != 1)
            posY += speedY;
        frame += walkSpeed;
        if (frame >= frameCount)
            frame = 0;
        sprite.setTextureRect(sf::IntRect(static_cast<int>(frame) * x, walk*y, w, l));
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        walk=3;
        if (static_cast<int>(frame) != 1)
            posY -= speedY;
        frame += walkSpeed;
        if (frame >= frameCount)
            frame = 0;
        sprite.setTextureRect(sf::IntRect(static_cast<int>(frame) * x, walk*y, w, l));//570
    }
    else
        sprite.setTextureRect(sf::IntRect(x,walk*y,w,l));

    sprite.setPosition(posX,posY);
}

void Enemy::move(Character& character){
    float walkSpeed=0;
    int frameCount=0;
    int x=0,y=0,w=0,l=0;
    float speedX=0,speedY=0;

    switch(category) {
        case (EnemyType::dragon):
            speedX=0.5;
            speedY=0.35;
            x=190;
            y=200;
            w=190;
            l=200;
            walkSpeed = 0.012;
            frameCount = 3;

            //bound enemy in the window

            break;

        case(EnemyType::skeleton):
            break; //TODO complete

    }
    //todo implement bresenham algoritm
    sprite.setPosition(posX,posY);

}

void Enemy::attack(){
    //todo
}

void Enemy::Render(Window &l_window) {
    l_window.Draw(sprite);
}
