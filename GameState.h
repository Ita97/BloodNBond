//
// Created by ciape on 19/11/17.
//

#ifndef B_B_GAMESTATE_H
#define B_B_GAMESTATE_H


#include "Game.h"

class GameState
{
public:

    Game* game;

    virtual void draw(const float dt) = 0;
    virtual void update(const float dt) = 0;
    virtual void handleInput() = 0;
};

#endif //B_B_GAMESTATE_H
