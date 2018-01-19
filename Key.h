//
// Created by ita on 29/12/17.
//

#ifndef BLOODBOND_KEY_H
#define BLOODBOND_KEY_H
#include <iostream>

enum class keyType{ stone, copper, silver, gold, titanium, skeleton};

class Key {
private:
    std::string name;
    keyType  material;
    bool isBroken;
    sf::Texture texture,invTexture;
    sf::Sprite sprite;

public:
    explicit Key(keyType type): material(type){
        isBroken=false;
        switch(type) { //todo add sprite
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
        }
        sprite.setTexture(texture);
    }
    void use(){
        if(isBroken)
            std::cout<<"E' gia stata usata!";
        isBroken=true;
    }
    keyType getMaterial(){
        return material;
    }
    const std::string &getName(){
        name=name+" Key";
        return name;
    }
    const sf::Sprite& getSprite(){
        return sprite;
    }
    const sf::Texture& getInventoryTexture(){
        return invTexture;
    }
};


#endif //BLOODBOND_KEY_H
