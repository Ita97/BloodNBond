//
// Created by ita on 10/02/18.
//
#include "Tile.h"

Tile::Tile(TileType type) {
    obstacle= nullptr;
    size.x=256;
    size.y=153,33;
    switch(type){
        case TileType::floor:
            texture.loadFromFile("./texture/map/tile/brick.png");
            break;
        case TileType::grass:
            texture.loadFromFile("./texture/map/tile/grass.png");
            break;
        case TileType:: wall:
            texture.loadFromFile("./texture/map/tile/wall.png");
            break;
        case TileType ::land:
            texture.loadFromFile("./texture/map/tile/dirt.png");
            break;
        case TileType ::dark:
            texture.loadFromFile("./texture/map/tile/blackGrass.jpg");
    }
    sprite.setTexture(texture);
}
