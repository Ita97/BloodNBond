//
// Created by ciape on 01/02/18.
//

#ifndef B_B_GAMESTATEEDITOR_H
#define B_B_GAMESTATEEDITOR_H




#include <SFML/System.hpp>
#include <string>
#include <map>

#include "GameState.h"
#include "Map.h"
#include "Gui.h"


enum class ActionState { NONE, PANNING, SELECTING };

class GameStateEditor : public GameState
{
private:

    ActionState actionState;

    sf::View gameView;
    sf::View guiView;

    Map map;

    sf::Vector2i panningAnchor;
    float zoomLevel;

    sf::Vector2i selectionStart;
    sf::Vector2i selectionEnd;

    Tile* currentTile;

    std::map<std::string, Gui> guiSystem;

public:

    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();

    GameStateEditor(Game* game);
};

#endif //B_B_GAMESTATEEDITOR_H
