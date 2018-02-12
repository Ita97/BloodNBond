//
// Created by ita on 10/02/18.
//

#include "Map.h"

void Map::create(sf::Vector2f position) {

    switch(type){
        case MapType::courtyard:
            for(int i=0; i<width*lenght;i++) {
                tile = new Tile(TileType::grass);
                tilesVector.push_back(tile);
            }
            obstacle= new Obstacle(ObstacleType::tree,0,300,200);
            obsVector.push_back(obstacle);
            obstacle=new Obstacle(ObstacleType::tree,2,670,400);
            obsVector.push_back(obstacle);
            break;
        case MapType::mansion :
            for(int i=0;i<width;i++){
                tile=new Tile(TileType::wall);
                tilesVector.push_back(tile);
            }
            for(int i=width;i<width*lenght;i++){
                tile=new Tile(TileType::floor);
                tilesVector.push_back(tile);
            }
            break;
        case MapType ::cemetery:
            for(int i=0; i<width*lenght;i++) {
                tile = new Tile(TileType::grass);
                tilesVector.push_back(tile);
            }
            obstacle= new Obstacle(ObstacleType::deadTree,0,300,200);
            obsVector.push_back(obstacle);
            obstacle=new Obstacle(ObstacleType::deadTree,2,670,400);
            obsVector.push_back(obstacle);
            obstacle=new Obstacle(ObstacleType::grave,0,150,300);
            obsVector.push_back(obstacle);
            break;
    }
    pos=position;
    firstTile.x=position.x-width*tile->getSize().x/2;
    firstTile.y=position.y-lenght*tile->getSize().y/2;

    float x,y;
    for(int i=0; i<lenght;i++) {
        for (int k = 0; k < width; k++){
            x=firstTile.x + k * tilesVector[i+k]->getSize().x;
            y=firstTile.y + i * tilesVector[i+k]->getSize().y;
            tilesVector[i*width+k]->setPosition(x,y);

        }
    }
}

void Map::Render(Window &window) {
    for(auto i:tilesVector)
        i->Render(window);
    for(auto i:obsVector)
        i->Render(window);
}