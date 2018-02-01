//
// Created by ciape on 19/11/17.
//
#include <SFML/Graphics.hpp>


#include "Tile.h"

void Tile::draw(sf::RenderWindow& window, float dt)
{


    /* Draw the tile */
    window.draw(this->sprite);


}


std::string tileTypeToStr(TileType type)
{
    switch(type)
    {

        case TileType::VOID:				return "Void";
        case TileType::GRASS:				return "Grass";
        case TileType::FOREST:				return "Forest";
        case TileType::WATER:				return "Water";
        case TileType::CHEST:			return "Chest";
        case TileType::NOTE:			return "Note";
        case TileType::DOOR:			return "Door";
        case TileType::ROAD:                return "Road";
    }
}