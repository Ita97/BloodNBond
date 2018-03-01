//
// Created by ita on 11/02/18.
//

#ifndef BLOODBOND_OBSTACLE_H
#define BLOODBOND_OBSTACLE_H


#include <SFML/Graphics.hpp>
#include "Key.h"

enum class ObstacleType{deadTree, tree, grave, forniture, woodpile, building, null};

class Obstacle {
private:
    sf::Vector2f position;
    sf::Vector2f area,collisionArea;
    sf::Texture texture;
    sf::Sprite sprite;
    ObstacleType type;
    keyType lock;
    bool unlockable,open;


public:
    explicit Obstacle(ObstacleType type,int select=0);
    sf::Vector2f getArea(){
        return area;
    }
    sf::Vector2f getPosition(){
        return position;
    }
    void setPosition(sf::Vector2f position){
        this->position=position;
        sprite.setPosition(position);
    }
    void Render(Window& window);

    sf::Vector2f getCollisionArea(){
        return collisionArea;
    }
    sf::Vector2f getCenterPosition(){
        return {position.x,position.y+area.y/2-getCollisionArea().y/2};
    }
    bool isUnlockable(){
        return unlockable;
    }
    bool unlock(keyType type){
        if(unlockable)
            open=(lock==type);
        return open;
    }
    ObstacleType getType(){
        return type;
    }

    bool isOpen(){
        return open;
    }
};


#endif //BLOODBOND_OBSTACLE_H
