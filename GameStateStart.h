//
// Created by ciape on 01/02/18.
//

#ifndef B_B_GAMESTATESTART_H
#define B_B_GAMESTATESTART_H



#include <SFML/Graphics.hpp>
#include <map>
#include <string>

#include "GameState.h"
#include "Gui.h"

class GameStateStart : public GameState
{
private:

    sf::View view;

    std::map<std::string, Gui> guiSystem;

    void loadgame();

public:

    virtual void draw(const float dt);
    virtual void update(const float dt);
    virtual void handleInput();

    GameStateStart(Game* game);
};

#endif //B_B_GAMESTATESTART_H
