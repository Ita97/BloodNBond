//
// Created by ita on 04/10/17.
//
#include "Medicine.h"

Medicine::Medicine(int value, medType type) : type(type){

    switch(this->type){
        case (medType ::hp):
            if(value<5) {
                name = "";
                texture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/medicine/beryllium.png");
                invTexture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/inventory/beryllium.png");
            }
            else{
                name="Super-";
                texture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/medicine/thorium.png");
                invTexture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/inventory/thorium.png");
            }
            name=name+"Potion";
            healtPoint=value;
            break;
        case(medType::sp):
            if(value<5){
                name="";
                texture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/medicine/antimon.png");
                invTexture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/inventory/antimon.png");
            }
            else{
                name="Super-";
                texture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/medicine/oxygen.png");
                invTexture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/inventory/oxygen.png");
            }
            name=name+"Elixir";
            sanityPoint=value;
            sprite.setTexture(texture);
    }
}

bool Medicine::operator==(const Medicine &right) {
    if(this->type==right.type)
        if(this->type==medType::hp) {
            if (this->healtPoint == right.healtPoint)
                return true;
        }
        else if(this->sanityPoint==right.sanityPoint)
            return true;
    return false;
}
