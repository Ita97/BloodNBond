//
// Created by ita on 02/10/17.
//

#ifndef BLOODBOND_INVENTORY_H
#define BLOODBOND_INVENTORY_H
template<typename T>
struct Object{
    T* ptr= nullptr;
    sf::Text name, description;
    int position;
    bool use=false;
};

#include <vector>
#include <algorithm>
#include <SFML/Graphics.hpp>


template <typename T>
class Inventory {
private:
    std::vector<T> elements;
    Object<T> object;

    sf::Texture inventoryBox,objectWindow_txt;
    sf::RectangleShape inventoryWindow;
    sf::Sprite box[8],objectWindow;
    sf::Vector2f windowSize, collisionArea;
    sf::Text inventoryName, text;
    sf::Font font1, font2;
    float scroll, WindowMaxSize;
    bool inventoryIsOpen, objectWindowIsOpen;


    bool isInsideArea(sf::Vector2i focus, sf::Vector2f target,sf::Vector2f area){
        if(focus.x>target.x-area.x && focus.x<target.x+area.x)
            if(focus.y>target.y-area.y && focus.y<target.y+area.y)
                return true;
        return false;
    }

public:
    explicit Inventory(const std::string &name = "Vault", std::vector<T> chest = {});

    bool displayObjectWindow(int pos){
        if(pos>=elements.size()||pos<0)
            return false;
        objectWindowIsOpen=true;
        return true;
    }
    void closeObjectWindow(){
        objectWindowIsOpen=false;
        object.use=false;
    }
    void openObjectWindow(){
        objectWindowIsOpen=true;
    }
    bool objectIsUsed(){
        return object.use;
    }
    T* getObject(){
        return object.ptr;
    }
    int getObjectPosition(){
        return object.position;
    }
    void SelectObject(sf::Vector2i mousePosition);
    void setObject(int pos);
    void update(){
        object.name.setString(object.ptr->getName());
        object.description.setString(object.ptr->getDescription());
    }

    bool getElement(T &el);
    bool throwElement(int pos);

    void setWindowSize(sf::Vector2f windowSize, float max);
    void openWindow();
    void closeWindow();
    bool isOpen(){
        return inventoryIsOpen;
    }
    void setName(const std::string &string);
    const sf::Vector2f getCollisionArea(){
        return collisionArea;
    }
    const sf::Vector2f getPosition();
    void reset(){
        elements.clear();
        object.ptr= nullptr;
    }
    void Render(sf::RenderWindow& l_window);
};
//Methods Definition

template <typename  T>
Inventory<T>::Inventory(const std::string &name, std::vector<T> chest)
        : elements(chest){
    objectWindow_txt.loadFromFile("./texture/inventory/object_description.png");
    objectWindow.setTexture(objectWindow_txt);
    objectWindow.setPosition(10,10);

    inventoryBox.loadFromFile("./texture/inventory/inventory_box.png");
    inventoryIsOpen=false;
    objectWindowIsOpen=false;
    scroll=windowSize.x;

    inventoryWindow.setSize(windowSize);
    inventoryWindow.setPosition(0,380);
    inventoryWindow.setFillColor(sf::Color(255,218,185)); //scroll color
    inventoryWindow.setOutlineThickness(2);
    inventoryWindow.setOutlineColor(sf::Color(101,67,33)); //dark brown color

    font1.loadFromFile("./Font/BeautyDemo.ttf");
    font2.loadFromFile("./Font/1942.ttf");
    inventoryName.setFont(font1);
    inventoryName.setFillColor(sf::Color(101,67,33));
    setName(name);

    text.setFont(font1);
    text.setPosition(inventoryWindow.getPosition().x+10,inventoryWindow.getPosition().y+5);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(25);

    object.description.setFont(font2);
    object.description.setFillColor(sf::Color::Black);
    object.description.setCharacterSize(12);
    object.description.setPosition(objectWindow_txt.getSize().x/2+objectWindow.getPosition().x,15+objectWindow.getPosition().y);

    object.name.setFont(font1);
    object.name.setFillColor(sf::Color::Black);
    object.name.setPosition(objectWindow.getPosition().x+10,objectWindow.getPosition().y);

    WindowMaxSize=0;


    collisionArea.x=15;
    collisionArea.y=50;
}


template <typename T>
bool Inventory<T>::getElement(T& el){
    if (elements.size()>=8) //se il numero di oggetti è maggiore o uguale alla capienza non aggiungere altri oggetti
        return false;
    elements.push_back(el);
    box[elements.size()-1].setTexture(el.getInventoryTexture());

    return true;
}


template <typename T>
bool Inventory<T>::throwElement(int pos) {
    sf::Texture texture;
    if(elements.empty()||pos>=elements.size())
        return false;

    auto it = elements.begin();
    for(it;it<elements.begin()+pos;it++)
        it++;
    elements.erase(it);
    for(int i=pos;i<elements.size();i++)
        box[i].setTexture(*box[i+1].getTexture());
    box[elements.size()].setTexture(inventoryBox);
    closeObjectWindow();
    object.ptr= nullptr;
    return true;
    }

template <typename T>
void Inventory<T>::setWindowSize(sf::Vector2f windowSize, float max) {
    this->windowSize = windowSize;
    WindowMaxSize=max;
    for(int i=0;i<8;i++){
        box[i].setTexture(inventoryBox);
        box[i].setOrigin(inventoryBox.getSize().x/2,inventoryBox.getSize().y/2);
        box[i].setPosition(WindowMaxSize-75-inventoryBox.getSize().x*i,inventoryWindow.getPosition().y+windowSize.y/2);
    }
}

template <typename T>
void Inventory<T>::openWindow() {
    inventoryIsOpen=true;
    if(object.ptr!= nullptr)
        openObjectWindow();
}

template <typename T>
void Inventory<T>::closeWindow() {
    inventoryIsOpen=false;
    objectWindowIsOpen=false;
}


template <typename T>
void Inventory<T>::Render(sf::RenderWindow &l_window) {

    inventoryName.setPosition(scroll-inventoryName.getCharacterSize(), inventoryWindow.getPosition().y+windowSize.y);
    l_window.draw(inventoryWindow);
    l_window.draw(inventoryName);

    if(inventoryIsOpen&&scroll<WindowMaxSize)
        scroll+=10;
    else if(inventoryIsOpen && scroll>=WindowMaxSize)
        for(auto& i:box)
            l_window.draw(i);
    else if(!inventoryIsOpen&& scroll>windowSize.x)
        scroll-=7;
    else if(!inventoryIsOpen&& scroll <=windowSize.x)
        scroll=windowSize.x;

    inventoryWindow.setSize(sf::Vector2f(scroll,windowSize.y));
    if(objectWindowIsOpen){
        l_window.draw(objectWindow);
        l_window.draw(object.ptr->getSprite());
        l_window.draw(object.description);
        l_window.draw(object.name);
    }

}

template <typename  T>
void Inventory<T>::setName(const std::string &string) {
    inventoryName.setString(string);
    if(string!="Vault")
        inventoryName.setRotation(-90);
}

template <typename  T>
void Inventory<T>::SelectObject(sf::Vector2i mousePosition) {
    if(inventoryIsOpen){
        int i=0;
        for(auto e:elements) {
            if (isInsideArea(mousePosition, box[i].getPosition(),
                             sf::Vector2f(inventoryBox.getSize().x / 2, inventoryBox.getSize().y / 2))) {
                setObject(i);
                displayObjectWindow(i);

            }
            i++;
        }
    }
    if(objectWindowIsOpen) {
        if (isInsideArea(mousePosition, sf::Vector2f(objectWindow.getPosition().x+objectWindow_txt.getSize().x - 10,
                                                     objectWindow.getPosition().y + 10), sf::Vector2f(10, 10))) {
            closeObjectWindow();    //chiudi finestra quando clikki la 'x'
            object.ptr= nullptr;
        }
        if(isInsideArea(mousePosition,sf::Vector2f(objectWindow.getPosition().x + objectWindow_txt.getSize().x/4+10,
                                                   objectWindow.getPosition().y + objectWindow_txt.getSize().y-14),sf::Vector2f(26.2,8.3)))
            throwElement(object.position);


        if(isInsideArea(mousePosition,sf::Vector2f(objectWindow.getPosition().x + 35,
                                                   objectWindow.getPosition().y + objectWindow_txt.getSize().y-14),sf::Vector2f(26.2,8.3))) {
            object.use=true;
        }
    }

}
template <typename  T>
void Inventory<T>::setObject(int pos) {
    object.use=false;
    object.ptr=&elements[pos];
    object.ptr->getSprite().setPosition(objectWindow.getPosition().x+objectWindow_txt.getSize().x/4,
                                        objectWindow.getPosition().y+objectWindow_txt.getSize().y/2);
    update();
    object.position=pos;
}

template <typename  T>
const sf::Vector2f Inventory<T>::getPosition() {
    float x=inventoryWindow.getPosition().x+inventoryWindow.getSize().x-collisionArea.x;
    float y=inventoryWindow.getPosition().y+collisionArea.y;
    return sf::Vector2f(x,y);
}

#endif //BLOODBOND_INVENTORY_H
