//
// Created by ita on 10/02/18.
//

#ifndef BLOODBOND_MAP_H
#define BLOODBOND_MAP_H

#include "Tile.h"
#include "Window.h"
#include "Obstacle.h"

enum class MapType{courtyard, mansion, cemetery};
class Map {
private:
    int lenght, width;
    sf::Vector2f pos;
    MapType type;
    Tile* tile;
    std::vector<Tile*> tilesVector;
    sf::Vector2f firstTile;
    Obstacle* obstacle;
    std::vector<Obstacle*> obsVector;
public:
    Map(MapType mapType,int width, int lenght):type(mapType),lenght(lenght),width(width){};
    ~Map(){}
    void create(sf::Vector2f position);
    void Render(Window& window);
    void setPosition(int x, int y){
        pos.x=x;
        pos.y=y;
    }
    sf::Vector2f getSize(){
        return sf::Vector2f(width*tile->getSize().x,lenght*tile->getSize().y);
    };
    sf::Vector2f getPosition(){
        return pos;
    }
    std::vector<Obstacle*> getObstacle(){
        return obsVector;
    }

};


#endif //BLOODBOND_MAP_H
