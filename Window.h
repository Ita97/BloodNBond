//
// Created by ita on 30/08/17.
//
#include <SFML/Graphics.hpp>
#include <stdlib.h>

#ifndef BLOODBOND_WINDOW_H
#define BLOODBOND_WINDOW_H


class Window {
public:
    Window();
    Window(const std::string& l_title, const sf::Vector2u& l_size); //'l' Hungarian notation for 'long'
    ~Window();

    void BeginDraw();
    void EndDraw();
    void Update();
    void ToggleFullscreen();

    bool IsDone();
    bool IsFullScreen();
    sf::Vector2u GetWindowSize();

    void Draw(sf::Drawable& l_drawable);

private:
    void Setup(const std::string& l_title, const sf::Vector2u& l_size);
    void Destroy();
    void Create();

    sf::RenderWindow m_window; //'m' Hungarian notation for 'member'
    sf::Vector2u m_windowSize;
    std::string m_windowTitle;
    bool m_isDone=false;
    bool m_isFullScreen;
};


#endif //BLOODBOND_WINDOW_H
