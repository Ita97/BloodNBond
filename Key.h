//
// Created by ita on 29/12/17.
//

#ifndef BLOODBOND_KEY_H
#define BLOODBOND_KEY_H
#include <iostream>

enum class keyType{ stone, copper, silver, gold, titanium, skeleton, null};

class Key {
private:
    std::string name, description;
    keyType  material;
    sf::Texture texture,invTexture;
    sf::Sprite sprite;

public:
    explicit Key(keyType type): material(type){
        switch(type) {
            case keyType::stone:
                name="Stone";
                break;
            case keyType::copper:
                name="Copper";
                texture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/key/copper_key.png");
                invTexture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/inventory/copper_key.png");
                break;
            case keyType::silver:
                name="Silver";
                texture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/key/silver_key.png");
                invTexture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/inventory/silver_key.png");
                break;
            case keyType::gold:
                name="Gold";
                texture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/key/gold_key.png");
                invTexture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/inventory/gold_key.png");
                break;
            case keyType::titanium:
                name="Titanium";
                break;
            case keyType::skeleton:
                name="Skeleton";
                texture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/key/skeleton_key.png");
                invTexture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/inventory/skeleton_key.png");
                break;
            default:
                name="";
        }

        name=name+" Key";
        description="It's an old "+name+".\nWho knows how it could\n be use for?\n\nPay attention: it's \nvery fragile!";
        sprite.setTexture(texture);
        sprite.setOrigin(texture.getSize().x/2,texture.getSize().y/2);
        sprite.setScale(0.4,0.4);
        sprite.setTextureRect(sf::IntRect(50,0,600,550));
    }

    keyType getMaterial(){
        return material;
    }
    const std::string& getDescription(){
        return description;
    }
    const std::string& getName(){
        return name;
    }
    sf::Sprite& getSprite(){
        return sprite;
    }
    const sf::Texture& getInventoryTexture(){
        return invTexture;
    }
};


#endif //BLOODBOND_KEY_H
