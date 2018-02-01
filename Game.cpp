//
// Created by ciape on 19/11/17.
//
#include <stack>

#include <SFML/Graphics.hpp>


#include "Game.h"
#include "GameState.h"


void Game::loadTiles()
{

    this->tileAtlas["grass"] =
            Tile(static_cast<const unsigned int>(this->tileSize), 1, texmgr.getRef("grass"),

                 TileType::GRASS, 50, 0, 1);
    tileAtlas["forest"] =
            Tile(static_cast<const unsigned int>(this->tileSize), 1, texmgr.getRef("forest"),

                 TileType::FOREST, 100, 0, 1);
    tileAtlas["water"] =
            Tile(static_cast<const unsigned int>(this->tileSize), 1, texmgr.getRef("water"),

                 TileType::WATER, 0, 0, 1);
    tileAtlas["chest"] =
            Tile(static_cast<const unsigned int>(this->tileSize), 2, texmgr.getRef("chest"),

                 TileType::CHEST, 300, 0, 1);
    tileAtlas["note"] =
            Tile(static_cast<const unsigned int>(this->tileSize), 2, texmgr.getRef("note"),

                 TileType::NOTE, 300, 0, 1);
    tileAtlas["door"] =
            Tile(static_cast<const unsigned int>(this->tileSize), 2, texmgr.getRef("door"),

                 TileType::DOOR, 300, 0, 1);
    tileAtlas["road"] =
            Tile(static_cast<const unsigned int>(this->tileSize), 1, texmgr.getRef("road"),

                 TileType::ROAD, 100, 0, 1);


}

void Game::loadTextures()
{
    texmgr.loadTexture("grass",         "/home/ciape/sprite/grass.png");
    texmgr.loadTexture("forest",        "/home/ciape/sprite/forest.png");
    texmgr.loadTexture("water",         "/home/ciape/sprite/water.png");
    texmgr.loadTexture("chest",   "/home/ciape/sprite/residential.png");
    texmgr.loadTexture("note",    "/home/ciape/sprite/commercial.png");
    texmgr.loadTexture("door",    "/home/ciape/sprite/industrial.png");
    texmgr.loadTexture("road",          "/home/ciape/sprite/road.png");

    texmgr.loadTexture("background",    "/home/ciape/sprite/background.png");
}

void Game::loadFonts()
{
    sf::Font font;
    font.loadFromFile("/home/ciape/sprite/font.ttf");
    this->fonts["main_font"] = font;


}

void Game::loadStylesheets()
{
    this->stylesheets["button"] = GuiStyle(&this->fonts.at("main_font"), 1,
                                           sf::Color(0xc6,0xc6,0xc6), sf::Color(0x94,0x94,0x94), sf::Color(0x00,0x00,0x00),
                                           sf::Color(0x61,0x61,0x61), sf::Color(0x94,0x94,0x94), sf::Color(0x00,0x00,0x00));
    this->stylesheets["text"] = GuiStyle(&this->fonts.at("main_font"), 0,
                                         sf::Color(0x00,0x00,0x00,0x00), sf::Color(0x00,0x00,0x00), sf::Color(0xff,0xff,0xff),
                                         sf::Color(0x00,0x00,0x00,0x00), sf::Color(0x00,0x00,0x00), sf::Color(0xff,0x00,0x00));


}

void Game::pushState(GameState* state)
{
    this->states.push(state);


}

void Game::popState()
{
    delete this->states.top();
    this->states.pop();


}



GameState* Game::peekState()
{
    if(this->states.empty()) return nullptr;
    return this->states.top();
}

void Game::gameLoop()
{
    sf::Clock clock;

    while(this->window.isOpen())
    {
        sf::Time elapsed = clock.restart();
        float dt = elapsed.asSeconds();

        if(peekState() == nullptr) continue;
        peekState()->handleInput();
        peekState()->update(dt);
        this->window.clear(sf::Color::Black);
        peekState()->draw(dt);
        this->window.display();
    }
}

Game::Game()
{
    this->loadTextures();
    this->loadTiles();
    this->loadFonts();
    this->loadStylesheets();

    this->window.create(sf::VideoMode(800, 600), "BLOOD & BOUNDS");
    this->window.setFramerateLimit(60);

    this->background.setTexture(this->texmgr.getRef("background"));
}

Game::~Game()
{
    while(!this->states.empty()) popState();
}