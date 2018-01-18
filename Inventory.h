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
    sf::Texture inventoryBox;
    sf::Sprite box[8];
    sf::Text name;
    float scroll;
    float WindowMaxSize;
    sf::Vector2f windowSize;
    std::vector<T> elements;
    sf::RectangleShape inventoryWindow;
    sf::Font invFont;
    sf::Text text;
    std::string elementName;
    bool isOpen;

public:
    explicit Inventory(const std::string &name = "Vault", std::vector<T> chest = {});

    bool getElement(T &el);
    bool trowElement(int pos);
    void setWindowSize(sf::Vector2f windowSize, float max) {
        this->windowSize = windowSize;
        WindowMaxSize=max;
        for(int i=0;i<8;i++){
            box[i].setTexture(inventoryBox);
            box[i].setOrigin(inventoryBox.getSize().x/2,inventoryBox.getSize().y/2);
            box[i].setPosition(max-75-inventoryBox.getSize().x*i,inventoryWindow.getPosition().y+windowSize.y/2);
        }
    }
    void openWindow();
    void closeWindow();
    void setName(std::string string);
    void Render(Window& l_window);
};
//Methods Definition

template <typename T>
bool Inventory<T>::getElement(T& el){ //todo add sprite
    if (elements.size()>=8) //se il numero di oggetti è maggiore o uguale alla capienza non aggiungere altri oggetti
        return false;

    elements.push_back(el);
    elementName=elementName+"o "+el.getName()+"  ";//ogni volta che aggiungo un elemento aggiorno la lista
    text.setString(elementName);
    return true;
}


template <typename T>
bool Inventory<T>::trowElement(int pos) {
    if(elements.empty()||pos>elements.size())
        return false;
    auto it = elements.begin();
    for(int i=0;i<pos;i++)
        it++;
    elements.erase(it);
    return true;
    }

template <typename T>
void Inventory<T>::openWindow() {
    isOpen=true;
}

template <typename T>
void Inventory<T>::closeWindow() {
    isOpen=false;
}


template <typename T>
void Inventory<T>::Render(Window &l_window) {

    name.setPosition(scroll-name.getCharacterSize(), inventoryWindow.getPosition().y+windowSize.y);
    l_window.Draw(inventoryWindow);
    l_window.Draw(name);

    if(isOpen&&scroll<WindowMaxSize)
        scroll+=6;
    else if(isOpen && scroll>=WindowMaxSize)
        for(auto& i:box)
            l_window.Draw(i);
    else if(!isOpen&& scroll>windowSize.x)
        scroll-=6;
    else if(!isOpen&& scroll <=windowSize.x)
        scroll=windowSize.x;

    inventoryWindow.setSize(sf::Vector2f(scroll,windowSize.y));
}

template <typename  T>
Inventory<T>::Inventory(const std::string &name, std::vector<T> chest)
        : elements(chest){
    inventoryBox.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/inventory/inventory_box.png");
    isOpen=false;
    scroll=windowSize.x;
    invFont.loadFromFile("/home/ita/CLionProjects/BloodBond/Font/BeautyDemo.ttf");
    inventoryWindow.setSize(windowSize);
    inventoryWindow.setPosition(0,380);
    inventoryWindow.setFillColor(sf::Color(255,218,185)); //scroll color
    inventoryWindow.setOutlineThickness(2);
    inventoryWindow.setOutlineColor(sf::Color(101,67,33)); //dark brown color
    text.setFont(invFont);
    this->name.setFont(invFont);
    this->name.setFillColor(sf::Color(101,67,33));
    text.setPosition(inventoryWindow.getPosition().x+10,inventoryWindow.getPosition().y+5);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(25);
    elementName="";
    WindowMaxSize=0;
    setName(name);
}

template <typename  T>
void Inventory<T>::setName(std::string string) {
    this->name.setString(string);
    if(string!="Vault")
        name.setRotation(-90);
}

#endif //BLOODBOND_INVENTORY_H
