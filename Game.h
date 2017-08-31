//
// Created by ita on 30/08/17.
//

#ifndef BLOODBOND_GAME_H
#define BLOODBOND_GAME_H

#include <SFML/Graphics.hpp>
#include "Window.h"

class Game {
public:
    Game();
    ~Game();

    void HandelInput();
    void Update();
    void Render();
    Window* GetWindow();
    //...TODO
private:
    void MoveHero();
    Window m_window;
    sf::Texture m_heroTexture;
    sf::Sprite m_hero;


};


#endif //BLOODBOND_GAME_H
