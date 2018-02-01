//
// Created by ciape on 19/11/17.
//

#ifndef B_B_MAP_H
#define B_B_MAP_H


#include <SFML/Graphics.hpp>

#include <string>
#include <map>
#include <vector>

#include "Tile.h"

#include <SFML/Graphics.hpp>


class Map
{
private:


public:

    unsigned int width;
    unsigned int height;

    std::vector<Tile> tiles;

    /* Resource map */
    std::vector<int> resources;

    unsigned int tileSize;

    unsigned int numRegions[1];

    /* 0 = Deselected, 1 = Selected, 2 = Invalid */
    std::vector<char> selected;
    unsigned int numSelected;

    /* Select the tiles within the bounds */
    void select(sf::Vector2i start, sf::Vector2i end, std::vector<TileType> blacklist);

    /* Deselect all tiles */
    void clearSelected();

    /* Load map from disk */
    void load(const std::string& filename, unsigned int width, unsigned int height,
              std::map<std::string, Tile>& tileAtlas);

    /* Save map to disk */
    void save(const std::string& filename);

    /* Draw the map */
    void draw(sf::RenderWindow& window, float dt);



    /* Blank map constructor */
    Map()
    {
        this->numSelected = 0;
        this->tileSize = 8;
        this->width = 0;
        this->height = 0;
        this->numRegions[0] = 1;
    }
    /* Load map from file constructor */
    Map(const std::string& filename, unsigned int width, unsigned int height,
        std::map<std::string, Tile>& tileAtlas)
    {
        this->numSelected = 0;
        this->tileSize = 8;
        load(filename, width, height, tileAtlas);
    }
};

#endif //B_B_MAP_H
