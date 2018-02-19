//
// Created by ita on 10/02/18.
//

#ifndef BLOODBOND_MAP_H
#define BLOODBOND_MAP_H

#include "Tile.h"
#include "Window.h"
#include "Obstacle.h"

enum class MapType{courtyard,frontyard, mansion, cemetery};
class Map {
private:
    int lenght, width;
    sf::Vector2f pos;
    MapType type;
    Tile* tile;
    std::vector<Tile*> tilesVector;
    sf::Vector2f tileSize;
    Obstacle* obstacle;
    std::vector<Obstacle*> obsVector;
    sf::Texture texture;
    bool visit;
public:
    Map(MapType mapType):type(mapType),tileSize(256,153.33),pos(480,240),visit(false){}
    ~Map(){}
    void create();
    void Render(Window& window);
    void update();
    sf::Vector2f getSize(){
        return {width*tile->getSize().x,lenght*tile->getSize().y};
    };
    sf::Vector2f getPosition(){
        return pos;
    }
    std::vector<Obstacle*>& getObstacle(){
        return obsVector;
    }
    void insertObstacle(int x, int y,ObstacleType type,int num=0 ){
        obstacle=new Obstacle(type,num);
        tilesVector[x+y*width]->setObstacle(obstacle);
        obsVector.push_back(obstacle);
    }
    MapType getType(){
        return type;
    }
    bool isVisited(){
        return visit;
    }
    sf::Vector2i getTile(sf::Vector2f position){
        int x=-1,y=-1;
        float num=pos.x-width*tileSize.x/2;
        while(num<position.x){
            num+=tileSize.x;
            x++;
        }
        num=pos.y-lenght*tileSize.y/2;
        while(num<position.y){
            num+=tileSize.y;
            y++;
        }
        return {x,y};
    }
    sf::Vector2f getTilePosition(int x, int y){
        return tilesVector[x+y*width]->getPosition();
    }
};


#endif //BLOODBOND_MAP_H
