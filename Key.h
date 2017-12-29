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
    Key(keyType type): material(type){
        isBroken=false;
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
