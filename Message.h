//
// Created by ita on 29/12/17.
//

#ifndef BLOODBOND_MESSAGE_H
#define BLOODBOND_MESSAGE_H

#include <string>

class Message {
private:
    std::string content, description, name;
    sf::Texture texture_close,texture_open, invTexture;
    sf::Sprite sprite;
    bool isOpen;
public:
    explicit Message(const std::string &strings=""){
        isOpen=false;
        name="Old Scroll";
        invTexture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/inventory/scroll_closed.png");
        texture_close.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/scroll/scroll.png");
        texture_open.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/scroll/message.png");
        sprite.setTexture(texture_close);
        sprite.setTextureRect(sf::IntRect(50,50,2000,2000));
        sprite.setOrigin(invTexture.getSize().x/2+930,invTexture.getSize().y/2+450);
        sprite.setScale(0.098,0.098);
        description="The paper is very\nold and fragile.\n\nIf you want read what\nthere is in this you\nhave only to open it.";

    }
    void setContent(std::string& message){
        content="It's an old, yellow \npaper.\n\nInside we can read:\n\n'"+message+"'.";
    }
    const std::string& getDescription(){
        if(isOpen)
            return content;
        return description;
    }
    const sf::Texture& getInventoryTexture(){
        return invTexture;
    }
    sf::Sprite& getSprite(){
        return sprite;
    }
    const std::string& getName(){
        return name;
    }
    void open(){
        if(!isOpen) {
            sprite.setTexture(texture_open);
            name="Message";
            isOpen = true;
        }
    };
};


#endif //BLOODBOND_MESSAGE_H
