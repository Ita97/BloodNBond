//
// Created by ita on 10/02/18.
//

#ifndef BLOODBOND_TILE_H
#define BLOODBOND_TILE_H

#include "Obstacle.h"
#include <SFML/Graphics.hpp>

enum class TileType{dark, grass, floor, wall, land};

class Tile {
private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f size;
    Obstacle* obstacle;

public:
    explicit Tile(TileType type);
    ~Tile(){
        delete obstacle;
    }
    void setObstacle(Obstacle* obs){
        delete obstacle;
        obstacle=obs;
        obstacle->setPosition(getPosition());
    }
    ObstacleType getObstacle(){
        if(obstacle!= nullptr)
            return obstacle->getType();
        return ObstacleType ::null;
    }
    void setPosition(float x, float y){
        sprite.setPosition(x, y);
    }
    sf::Vector2f getPosition(){
        return {sprite.getPosition().x+size.x/2,sprite.getPosition().y+size.y/2};
    }
    void Render(sf::RenderWindow& window){
        window.draw(sprite);
    }
    sf::Vector2f getSize(){
        return size;
    }
};


#endif //BLOODBOND_TILE_H
