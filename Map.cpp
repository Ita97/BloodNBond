#include <SFML/Graphics.hpp>

#include <fstream>


#include "Map.h"


/* Load map from disk */
void Map::load(const std::string& filename, unsigned int width, unsigned int height,
               std::map<std::string, Tile>& tileAtlas)
{
    std::ifstream inputFile;
    inputFile.open(filename, std::ios::in | std::ios::binary);

    this->width = width;
    this->height = height;

    for(int pos = 0; pos < this->width * this->height; ++pos)
    {
        this->resources.push_back(255);
        this->selected.push_back(0);

        TileType tileType;
        inputFile.read((char*)&tileType, sizeof(int));
        switch(tileType)
        {

            case TileType::VOID:
            case TileType::GRASS:
                this->tiles.push_back(static_cast<Tile &&>(tileAtlas.at("grass")));
                break;
            case TileType::FOREST:
                this->tiles.push_back(static_cast<Tile &&>(tileAtlas.at("forest")));
                break;
            case TileType::WATER:
                this->tiles.push_back(static_cast<Tile &&>(tileAtlas.at("water")));
                break;
            case TileType::CHEST:
                this->tiles.push_back(static_cast<Tile &&>(tileAtlas.at("chest")));
                break;
            case TileType::NOTE:
                this->tiles.push_back(static_cast<Tile &&>(tileAtlas.at("note")));
                break;
            case TileType::DOOR:
                this->tiles.push_back(static_cast<Tile &&>(tileAtlas.at("door")));
                break;
            case TileType::ROAD:
                this->tiles.push_back(static_cast<Tile &&>(tileAtlas.at("road")));
                break;
        }
        Tile& tile = this->tiles.back();
        inputFile.read((char*)&tile.tileVariant, sizeof(int));
        inputFile.read((char*)&tile.regions, sizeof(int)*1);

    }

    inputFile.close();


}

void Map::save(const std::string& filename)
{
    std::ofstream outputFile;
    outputFile.open(filename, std::ios::out | std::ios::binary);

    for(auto tile : this->tiles)
    {
        outputFile.write((char*)&tile.tileType, sizeof(int));
        outputFile.write((char*)&tile.tileVariant, sizeof(int));
        outputFile.write((char*)&tile.regions, sizeof(int)*3);

    }

    outputFile.close();


}

void Map::draw(sf::RenderWindow& window, float dt)
{
    for(int y = 0; y < this->height; ++y)
    {
        for(int x = 0; x < this->width; ++x)
        {
            /* Set the position of the tile in the 2d world */
            sf::Vector2f pos;
            pos.x = (x - y) * this->tileSize + this->width * this->tileSize;
            pos.y = (x + y) * this->tileSize * 0.5;
            this->tiles[y*this->width+x].sprite.setPosition(pos);

            /* Change the colour if the tile is selected */
            if(this->selected[y*this->width+x])
                this->tiles[y*this->width+x].sprite.setColor(sf::Color(0x7d, 0x7d, 0x7d));
            else
                this->tiles[y*this->width+x].sprite.setColor(sf::Color(0xff, 0xff, 0xff));

            /* Draw the tile */
            this->tiles[y*this->width+x].draw(window, dt);
        }
    }

}



void Map::clearSelected()
{
    for(auto& tile : this->selected) tile = 0;

    this->numSelected = 0;


}

void Map::select(sf::Vector2i start, sf::Vector2i end, std::vector<TileType> blacklist)
{
    /* Swap coordinates if necessary */
    if(end.y < start.y) std::swap(start.y, end.y);
    if(end.x < start.x) std::swap(start.x, end.x);

    /* Clamp in range */
    if(end.x >= this->width)        end.x = this->width - 1;
    else if(end.x < 0)                 end.x = 0;
    if(end.y >= this->height)         end.y = this->height - 1;
    else if(end.y < 0)                 end.y = 0;
    if(start.x >= this->width)         start.x = this->width - 1;
    else if(start.x < 0)             start.x = 0;
    if (start.y >= this->height)     start.y = this->height - 1;
    else if(start.y < 0)             start.y = 0;

    for(int y = start.y; y <= end.y; ++y)
    {
        for(int x = start.x; x <= end.x; ++x)
        {
            /* Check if the tile type is in the blacklist. If it is, mark it as
             * invalid, otherwise select it */
            this->selected[y*this->width+x] = 1;
            ++this->numSelected;
            for(auto type : blacklist)
            {
                if(this->tiles[y*this->width+x].tileType == type)
                {
                    this->selected[y*this->width+x] = 2;
                    --this->numSelected;
                    break;
                }
            }
        }
    }


}