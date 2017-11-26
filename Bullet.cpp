//
// Created by ita on 20/11/17.
//

#include "Bullet.h"

Bullet::Bullet(sf::Vector2f size) {
    sf::Color bulletColor(117,102,63); //bronzo
    bullet.setSize(size);
    bullet.setFillColor(bulletColor);
    bullet.setOrigin(size.x/2,size.y/2);
}

void Bullet::fire(int speed, int direction, sf::Vector2f range){
        switch(direction) {
            case 0: //down
                bullet.move(speed/2,0);
                break;
            case 1: //right
                bullet.move(0,speed);
                break;
            case 2: //up
                bullet.move(-speed/2,0);
                break;
            case 3: //left
                bullet.move(0,-speed);
                break;
        }

}

void Bullet::Render(Window& l_window){
    l_window.Draw(bullet);
}
