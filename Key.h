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
    sf::Texture texture;
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
                break;
            case keyType::silver:
                name="Silver";
                break;
            case keyType::gold:
                name="Gold";
                break;
            case keyType::titanium:
                name="Titanium";
                break;
            case keyType::skeleton:
                name="Skeleton";
                break;
        }
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
};


#endif //BLOODBOND_KEY_H
