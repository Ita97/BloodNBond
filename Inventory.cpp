//
// Created by ita on 02/10/17.
//

#include "Inventory.h"

template <typename T>
bool Inventory<T>::getElement(T& el){
    if (elements.size()>=this->maxSize) //se la il numero di oggetti è maggiore o uguale alla capienza non aggiungere altri oggetti
        return false;
    elements.push_back(el);
    return true;
}

template <typename T>
bool Inventory<T>::trowElement(T& el) {
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

    inventoryWindow=new sf::RectangleShape;
    inventoryWindow->setSize(sf::Vector2f(100,70));
    inventoryWindow->setPosition(0,0);
    inventoryWindow->setFillColor(sf::Color(211,211,211,120)); //silver color
    inventoryWindow->setOutlineThickness(5);
    inventoryWindow->setOutlineColor(sf::Color::Black);

    text= new sf::Text;
    text->setFont(invFont);
    text->setPosition(inventoryWindow->getPosition().x+10,inventoryWindow->getPosition().y+5);
    text->setFillColor(sf::Color::Black);
    text->setCharacterSize(10);

    isOpen=true;
    elementName="";

    for(int i=0;i<limit;i++){
        elementName=elementName+"-"+elements[i].getName()+"/n";//todo finish: find a way to insert a string in stl
    }

    text->setString(elementName);
}

template <typename T>
void Inventory<T>::closeWindow() {
    delete inventoryWindow;
    delete text;
    isOpen=false;
}

template <typename T>
void Inventory<T>::Render(Window &l_window) {
    l_window.Draw(*inventoryWindow);
    l_window.Draw(*text);
}