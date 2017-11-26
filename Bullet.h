//
// Created by ita on 20/11/17.
//

#ifndef BLOODBOND_BULLET_H
#define BLOODBOND_BULLET_H


#include "Window.h"
#include <SFML/Graphics.hpp>

class Bullet {
private:
    sf::RectangleShape  bullet;
public:
    explicit Bullet(sf::Vector2f size);
    void fire(int speed, int direction, sf::Vector2f range);

    sf::Vector2f getPosition(){
        return bullet.getPosition();
    }
    void setPosition(sf::Vector2f position){
        bullet.setPosition(position);
    }
    void Render(Window& l_window);
};


#endif //BLOODBOND_BULLET_H
