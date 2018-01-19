//
// Created by ita on 29/12/17.
//

#ifndef BLOODBOND_MESSAGE_H
#define BLOODBOND_MESSAGE_H

#include <string>

class Message {
private:
    std::string content;
    sf::Texture texture_close,texture_open, invTexture;
    sf::Sprite sprite_close, sprite_open;
public:
    explicit Message(const std::string &strings=""){
        invTexture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/inventory/scroll_close.png");
        texture_close.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/scroll/scroll.png");
        texture_open.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/scroll/message.png");
        sprite_close.setTexture(texture_close);
        sprite_open.setTexture(texture_open);
    }
    void setContent(std::string& message){
        content=message;
    }
    std::string readMessage(){
        return content;
    }
    const sf::Texture& getInventoryTexture(){
        return invTexture;
    }
};


#endif //BLOODBOND_MESSAGE_H
