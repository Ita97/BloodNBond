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
    int size;
    std::vector<T> elements;
    sf::RectangleShape *inventoryWindow;
    sf::Font invFont;
    sf::Text *text;
    int rollCounter;
    bool isOpen;
    //todo se vuoi aggiungi categoria..

public:
    explicit Inventory(int size=15, std:: vector<T> chest={}): size(size), elements(chest){
        rollCounter=0;
        isOpen=false;
        invFont.loadFromFile("/home/ita/CLionProjects/BloodBond/Font/BeautyDemo.ttf");
        inventoryWindow= nullptr;
        text= nullptr;
    }
    int getSize() const{
        return size;
    }
    void setSize(int s){
        size=s;
    }
    bool getElement(T& el);
    bool trowElement(T el);

    void openWindow();
    void closeWindow();
    void Render(Window& l_window);

};


#endif //BLOODBOND_INVENTORY_H
