//
// Created by ita on 20/11/17.
//

#include "Bullet.h"

Bullet::Bullet() {
    bullet.setFillColor(sf::Color(117,102,63,100)); //bronze color

}

void Bullet::fire(float speed, int direction) {

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
        }

}


void Bullet::Render(Window& l_window){

    l_window.Draw(bullet);
}
