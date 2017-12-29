//
// Created by ita on 02/10/17.
//

#ifndef BLOODBOND_INVENTORY_H
#define BLOODBOND_INVENTORY_H


#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>
#include "Window.h"
template <typename T>

class Inventory {
private:
    int maxSize;
    std::vector<T> elements;
    sf::RectangleShape *inventoryWindow;
    sf::Font invFont;
    sf::Text *text;
    bool isOpen;
    //todo se vuoi aggiungi categoria..

public:
    explicit Inventory(int size=10, std:: vector<T> chest={}): maxSize(size), elements(chest){
        isOpen=false;
        invFont.loadFromFile("/home/ita/CLionProjects/BloodBond/Font/BeautyDemo.ttf");
        inventoryWindow= nullptr;
        text= nullptr;
    }
    int getMaxSize() const{
        return maxSize;
    }
    void setMaxSize(int s){
        maxSize=s;
    }
    bool getElement(T& el);
    bool trowElement(T& el);

    void openWindow();
    void closeWindow();
    void Render(Window& l_window);

};


#endif //BLOODBOND_INVENTORY_H
