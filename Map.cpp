//
// Created by ita on 10/02/18.
//

#include "Map.h"

void Map::create() {
    float x,y;
    switch(type){


        case MapType::courtyard:

            width=4; lenght=4;
            for(int i=0; i<lenght;i++) {
                for (int k = 0; k < width; k++){
                    x=pos.x-width*tileSize.x/2 + k * tileSize.x;
                    y=pos.y-lenght*tileSize.y/2 + i * tileSize.y;

                    tile = new Tile(TileType::grass);
                    tile->setPosition(x,y);
                    tilesVector.push_back(tile);
                }
            }

            //set obstacles
            insertObstacle(1,1,ObstacleType::tree);
            insertObstacle(3,2,ObstacleType::tree,2);
            insertObstacle(2,2,ObstacleType::box);
            obstacle->setAction("You got 'Old Sword'.\nYou got 'Thorium Conyxa'.\nYou got 'Oxygen Conyxa'.");

            break;


        case MapType ::frontyard:

            width=4; lenght=3;
            pos.y=320;

            for(int i=0; i<lenght;i++) {
                for (int k = 0; k < width; k++){
                    x=pos.x-width*tileSize.x/2 + k * tileSize.x;
                    y=pos.y-lenght*tileSize.y/2 + i * tileSize.y;

                    tile = new Tile(TileType::grass);
                    tile->setPosition(x,y);
                    tilesVector.push_back(tile);
                }
            }

            //set obstacles
            insertObstacle(2,0,ObstacleType::null);
            insertObstacle(0,0,ObstacleType::null);
            insertObstacle(3,0,ObstacleType::null);
            insertObstacle(1,0,ObstacleType::building);
            break;


        case MapType::mansion :

            width=4; lenght=4;

            for(int i=0;i<width;i++){
                x=pos.x-width*tileSize.x/2 + i * tileSize.x;
                y=pos.y-lenght*tileSize.y/2;

                tile=new Tile(TileType::wall);
                tile->setPosition(x,y);
                tilesVector.push_back(tile);
                insertObstacle(i,0,ObstacleType::null);
            }
            for(int i=1;i<lenght;i++){
                for (int k = 0; k < width; k++){
                    x=pos.x-width*tileSize.x/2 + k * tileSize.x;
                    y=pos.y-lenght*tileSize.y/2 + i * tileSize.y;

                    tile=new Tile(TileType::floor);
                    tile->setPosition(x,y);
                    tilesVector.push_back(tile);
                }
            }
            //set obstacles
            insertObstacle(0,1,ObstacleType::forniture); //table
            break;


        case MapType ::cemetery:
            width=4; lenght=4;

            for(int i=0; i<lenght;i++) {
                for (int k = 0; k < width; k++){
                    x=pos.x-width*tileSize.x/2 + k * tileSize.x;
                    y=pos.y-lenght*tileSize.y/2 + i * tileSize.y;

                    tile = new Tile(TileType::dark);
                    tile->setPosition(x,y);
                    tilesVector.push_back(tile);
                }
            }
            //set obstacles
            insertObstacle(1,1,ObstacleType::deadTree);
            insertObstacle(3,2,ObstacleType::deadTree,2);
            insertObstacle(0,2,ObstacleType::grave);
            insertObstacle(2,0,ObstacleType::box);
            obstacle->setAction("You got 'Skeleton Key'.\nYou got 'Revolver'.");

            break;
    }


    visit=true;
}

void Map::update() {
    auto pos=obsVector.cbegin();
    for(auto i:obsVector){
        if(i->isUnlockable()&&i->isOpen()) {
            sf::Vector2i tile=getTile(i->getPosition());
            ObstacleType type=i->getType();
            obsVector.erase(pos);
            insertObstacle(tile.x,tile.y,type,1);
        }
         pos++;
    }
}


void Map::Render(sf::RenderWindow &window) {
    for(auto i:tilesVector)
        i->Render(window);
}
