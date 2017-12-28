//
// Created by ita on 02/10/17.
//

#include "Inventory.h"

template <typename T>
bool Inventory<T>::getElement(T el){
    if (element.size()>this->size)
        return false;
    element.push_back(el);
    return true;
}

template <typename T>
bool Inventory<T>::trowElement(T el) {
    if(element.empty())
        return false;

    for (auto it = element.begin(); it !=element.end(); it++) {
        if (el == element[it]){
            element.erase(it);
            return true;
        }
    }


}
template <typename T>
void Inventory<T>::openWindow() {
    std::string elementName=0;
    int firstLine=0;
    inventoryWindow.setSize(sf::Vector2f(100,70));
    inventoryWindow.setPosition(0,0);
    inventoryWindow.setFillColor(sf::Color(211,211,211,120)); //silver color
    inventoryWindow.setOutlineThickness(5);
    inventoryWindow.setOutlineColor(sf::Color::Black);
    isOpen=true;

    if(sf::Mouse::getPosition().x>inventoryWindow.getOrigin().x&& sf::Mouse::getPosition().x<inventoryWindow.getSize().x+inventoryWindow.getOrigin().x)
        if (sf::Mouse::getPosition().y>inventoryWindow.getOrigin().y&& sf::Mouse::getPosition().y<inventoryWindow.getSize().y+inventoryWindow.getOrigin().y)
            firstLine=firstLine+rollCounter;

    for(int i=firstLine;i<9+firstLine;i++){
        elementName=elementName+element[i].getName()+"/n";//todo finish: find a way to insert a string in stl
    }

    text.setString(elementName);
    elementName=0;
}
