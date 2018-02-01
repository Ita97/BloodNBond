//
// Created by ciape on 19/11/17.
//

#ifndef B_B_TILE_H
#define B_B_TILE_H


#include <SFML/Graphics.hpp>
#include <vector>



enum class TileType { VOID, GRASS, FOREST, WATER, CHEST, NOTE, DOOR, ROAD };

std::string tileTypeToStr(TileType type);

class Tile
{
public:

    sf::Sprite sprite;

    TileType tileType;

    /* Tile variant, allowing for different looking versions of the
     * same tile */
    int tileVariant;

    /* Region IDs of the tile, tiles in the same region are connected. */
    unsigned int regions[1];

    /* Integrity of the tile */
    unsigned int Integrity;



    /* Tells you if a tile is Flamable */
    unsigned int Flamable;
    /* Tells you if you can lift an object */
    unsigned int Liftable;

    /* Constructor */
    Tile() { }
    Tile(const unsigned int tileSize, const unsigned int height, sf::Texture& texture,

         const TileType tileType, const unsigned int Integrity, const unsigned int Flamable,
         const unsigned int Liftable)
    {
        this->tileType = tileType;
        this->tileVariant = 0;
        this->regions[0] = 0;

        this->Integrity = Integrity;

        this->Flamable = Flamable;
        this->Liftable = Liftable;

        this->sprite.setOrigin(sf::Vector2f(0.0f, tileSize*(height-1)));
        this->sprite.setTexture(texture);

    }

    void draw(sf::RenderWindow& window, float dt);



};

#endif //B_B_TILE_H
