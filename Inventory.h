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
    sf::RectangleShape inventoryWindow;
    sf::Font invFont;
    sf::Text text;
    bool isOpen;
    //todo se vuoi aggiungi categoria..

public:
    explicit Inventory(int size=10, std:: vector<T> chest={});
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

//Methods Definition

template <typename T>
bool Inventory<T>::getElement(T& el){
    if (elements.size()>=maxSize) //se il numero di oggetti è maggiore o uguale alla capienza non aggiungere altri oggetti
        return false;

    elements.push_back(el);
    return true;
}


template <typename T>
bool Inventory<T>::trowElement(T& el) {//todo make it better
    if(elements.empty())
        return false;

    for (auto it = elements.begin(); it !=elements.end(); it++) {
        if (el == elements[it]){
            elements.erase(it);
            return true;
        }
    }


}
template <typename T>
void Inventory<T>::openWindow() {

    std::string elementName;
    long int limit=maxSize;

    if(elements.size()<limit)
        limit=elements.size();

    isOpen=true;
    elementName="";

    for(int i=0;i<limit;i++){
        elementName=elementName+"-"+elements[i].getName()+"/n";//todo andrebbe aggiornato all'aggiunta di ogni elemento
    }

    text.setString(elementName);
}

template <typename T>
void Inventory<T>::closeWindow() {
    isOpen=false;
}

template <typename T>
void Inventory<T>::Render(Window &l_window) {
    if(isOpen){
        l_window.Draw(inventoryWindow);
        l_window.Draw(text);
    }
}
template <typename  T>
Inventory<T>::Inventory(int size, std::vector<T> chest) : maxSize(size), elements(chest){
    isOpen=false;
    invFont.loadFromFile("/home/ita/CLionProjects/BloodBond/Font/BeautyDemo.ttf");
    inventoryWindow.setSize(sf::Vector2f(100,70));
    inventoryWindow.setPosition(0,0);
    inventoryWindow.setFillColor(sf::Color(211,211,211,120)); //silver color
    inventoryWindow.setOutlineThickness(5);
    inventoryWindow.setOutlineColor(sf::Color::Black);

    text.setFont(invFont);
    text.setPosition(inventoryWindow.getPosition().x+10,inventoryWindow.getPosition().y+5);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(10);
}

#endif //BLOODBOND_INVENTORY_H
