//
// Created by ita on 10/02/18.
//

#ifndef BLOODBOND_TILE_H
#define BLOODBOND_TILE_H


#include <SFML/Graphics.hpp>
#include "Window.h"
#include "Obstacle.h"

enum class TileType{dark, grass, floor, wall, land};

class Tile {
private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f size;
    Obstacle* obstacle;

public:
    Tile(TileType type){
        obstacle= nullptr;
        size.x=256;
        size.y=153,33;
        switch(type){
            case TileType::floor:
                texture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/map/brick.png");
                break;
            case TileType::grass:
                texture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/map/grass.png");
                break;
            case TileType:: wall:
                texture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/map/wall.png");
                break;
            case TileType ::land:
                texture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/map/dirt.png");
                break;
            case TileType ::dark:
                texture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/map/blackGrass.jpg");
        }
        sprite.setTexture(texture);
    }
    ~Tile(){
        delete obstacle;
    }
    void setObstacle(Obstacle* obs){
        obstacle=obs;
        obstacle->setPosition(getPosition());
    }
    Obstacle* getObstacle(){
        return obstacle;
    }
    void setPosition(float x, float y){
        sprite.setPosition(x, y);
    }
    sf::Vector2f getPosition(){
        return {sprite.getPosition().x+size.x/2,sprite.getPosition().y+size.y/2};
    }
    void Render(Window& window){
        window.Draw(sprite);
    }
    sf::Vector2f getSize(){
        return size;
    }
};


#endif //BLOODBOND_TILE_H
