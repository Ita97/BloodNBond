//
// Created by ita on 20/11/17.
//

#include "Bullet.h"

Bullet::Bullet(int direction, sf::Vector2f pos):direction(direction), beginningPos(pos) {
    bullet.setFillColor(sf::Color(117,102,63,100)); //bronze
    bullet.setPosition(beginningPos.x,beginningPos.y+10);
}

void Bullet::fire(float speed) {

        switch(direction) {
            case 0: //down
                bullet.setRotation(90);
                bullet.move(0, speed / 2);
                break;
            case 1: //right
                bullet.setRotation(0);
                bullet.move(speed, 0);
                break;
            case 2: //up
                bullet.setRotation(90);
                bullet.move(0,-speed/2);
                break;
            case 3: //left
                bullet.setRotation(0);
                bullet.move(-speed,0);
                break;
            default:
                break;
        }

}


void Bullet::Render(sf::RenderWindow& l_window){

    l_window.draw(bullet);
}
