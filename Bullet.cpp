//
// Created by ita on 20/11/17.
//

#include "Bullet.h"

Bullet::Bullet() {
    sf::Color bronze(117,102,63); //bronze color
    bullet.setFillColor(bronze);

}

void Bullet::fire(int speed, int direction){
        switch(direction) {
            case 0: //down
                bullet.move(0,speed/2);
                break;
            case 1: //right
                bullet.move(speed,0);
                break;
            case 2: //up
                bullet.move(0,-speed/2);
                break;
            case 3: //left
                bullet.move(-speed,0);
                break;
        }

}

void Bullet::Render(Window& l_window){
    l_window.Draw(bullet);
}
