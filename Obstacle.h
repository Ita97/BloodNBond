//
// Created by ita on 11/02/18.
//

#ifndef BLOODBOND_OBSTACLE_H
#define BLOODBOND_OBSTACLE_H


#include <SFML/Graphics.hpp>
#include "Window.h"

enum class ObstacleType{deadTree, tree, grave, forniture, woodpile};

class Obstacle {
private:
    sf::Vector2f position;
    sf::Vector2f area;
    sf::Texture texture;
    sf::Sprite sprite;
    ObstacleType type;

public:
    Obstacle(ObstacleType type,int select, int x=0, int y=0);
    sf::Vector2f getArea(){
        return area;
    }
    sf::Vector2f getPosition(){
        return position;
    }
    void setPosition(sf::Vector2f position){
        this->position=position;
    }
    void Render(Window& window);
};


#endif //BLOODBOND_OBSTACLE_H
