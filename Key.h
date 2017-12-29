//
// Created by ita on 29/12/17.
//

#ifndef BLOODBOND_KEY_H
#define BLOODBOND_KEY_H
#include <iostream>

enum class keyType{wood, stone, brass, copper, silver, gold, platinum, titanium, skeleton};

class Key {
private:
    keyType  material;
    bool isBroken;

public:
    explicit Key(keyType type): material(type){
        isBroken=false;
        switch(type) { //todo add sprite
            case keyType::wood:
                break;
            case keyType::stone:
                break;
            case keyType::brass:
                break;
            case keyType::copper:
                break;
            case keyType::silver:
                break;
            case keyType::gold:
                break;
            case keyType::platinum:
                break;
            case keyType::titanium:
                break;
            case keyType::skeleton:
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
};


#endif //BLOODBOND_KEY_H
