//
// Created by ita on 01/11/17.
//

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "Enemy.h"
#include "Window.h"
Enemy::Enemy(int hp, int x, int y, int stg, Weapon *weapon, EnemyType type): Character(hp, x, y, weapon), strength(stg), category(type){
    switch(category) {
        case (EnemyType::dragon):
            t_enemy.loadFromFile("/home/ita/CLionProjects/BloodBond/pic/dragon.png");
            enemy.setTextureRect(sf::IntRect(190, 200, 190, 200));//intRect(left, top, width, length)
            frame = 1;
            break;

        case (EnemyType::ghost):
            break;//TODO complete
        case(EnemyType::zombie):
            break;//TODO complete
    }
        enemy.setTexture(t_enemy);
        enemy.setPosition(x, y);


}

void Enemy::move() {
    float walkSpeed;
    int frameCount;
    switch(category) {
        case (EnemyType::dragon):

            walkSpeed = 0.011;
            frameCount = 3;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                if (static_cast<int>(frame) != 1)
                    posX += 0.6;
                frame += walkSpeed;
                if (frame >= frameCount)
                    frame = 0;
                enemy.setTextureRect(sf::IntRect(static_cast<int>(frame) * 190, 390, 190, 200));
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                int l_frame;
                if (static_cast<int>(frame) != 1)
                    posX -= 0.6;
                frame += walkSpeed;
                if (frame >= 3)
                    frame = 0;
                if (static_cast<int>(frame) == 0) l_frame = 2;
                if (static_cast<int>(frame) == 1) l_frame = 1;
                if (static_cast<int>(frame) == 2) l_frame = 0;

                enemy.setTextureRect(sf::IntRect(l_frame * 190, 200, 190, 200));

            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                if (static_cast<int>(frame) != 1)
                    posY += 0.35;
                frame += walkSpeed;
                if (frame >= frameCount)
                    frame = 0;
                enemy.setTextureRect(sf::IntRect(static_cast<int>(frame) * 190, 0, 190, 200));
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                if (static_cast<int>(frame) != 1)
                    posY -= 0.35;
                frame += walkSpeed;
                if (frame >= frameCount)
                    frame = 0;
                enemy.setTextureRect(sf::IntRect(static_cast<int>(frame) * 190, 570, 190, 250));
            }

            //bound enemy in the window
            if (posX <= 0) posX = 0;
            if (posX >= 770) posX = 770;
            if (posY <= -50) posY = -50;
            if (posY >= 295) posY = 295;
            break;

        case(EnemyType::zombie):
            break; //TODO complete

        case(EnemyType::ghost):
            break; //TODO complete
    }
    enemy.setPosition(posX,posY);
}

void Enemy::Render(Window &l_window) {
    l_window.Draw(enemy);
}

void Enemy::attack(Character& enemy){}