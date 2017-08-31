//
// Created by ita on 30/08/17.
//

#include "Game.h"

Game::Game():m_window("Chapter 1", sf::Vector2u(800,600)) {
    //TODO setting class members
    m_heroTexture.loadFromFile("character.png");
    m_hero.setTexture(m_heroTexture);
};