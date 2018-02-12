//
// Created by ita on 10/02/18.
//

#ifndef BLOODBOND_TILE_H
#define BLOODBOND_TILE_H


#include <SFML/Graphics.hpp>
#include "Window.h"

enum class TileType{ grass, floor, wall, land};

class Tile {
private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f size;

public:
    Tile(TileType type){
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

        }
        sprite.setTexture(texture);
    }

    void setPosition(float x, float y){
        sprite.setPosition(x, y);
    }
    void Render(Window& window){
        window.Draw(sprite);
    }
    sf::Vector2f getSize(){
        return size;
    }
};


#endif //BLOODBOND_TILE_H
