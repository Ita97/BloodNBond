//
// Created by ciape on 19/11/17.
//

#ifndef B_B_GAME_H
#define B_B_GAME_H



#include <stack>
#include <map>
#include <string>
#include <SFML/Graphics.hpp>

#include "TextureManager.h"
#include "Tile.h"

#include "Gui.h"

class GameState;

class Game
{
private:

    void loadTextures();
    void loadTiles();
    void loadStylesheets();
    void loadFonts();

public:

    const static int tileSize = 8;

    std::stack<GameState*> states;

    sf::RenderWindow window;
    TextureManager texmgr;
    sf::Sprite background;

    std::map<std::string, Tile> tileAtlas;
    std::map<std::string, GuiStyle> stylesheets;
    std::map<std::string, sf::Font> fonts;

    void pushState(GameState* state);
    void popState();

    GameState* peekState();

    void gameLoop();

    Game();
    ~Game();
};



#endif //B_B_GAME_H
