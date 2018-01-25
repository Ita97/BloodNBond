//
// Created by ita on 04/10/17.
//
#include "Medicine.h"
#include <sstream>
Medicine::Medicine(int value, medType type) : type(type){
    std::string string, points;
    std::stringstream num;
    switch(this->type){
        case (medType ::hp):
            string="healt problems.";
            points="Healt";
            if(value<5) {
                name = "Beryllium-Conyxa";
                texture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/medicine/beryllium.png");
                invTexture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/inventory/beryllium.png");
            }
            else{
                name="Thorium-Conyxa";
                texture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/medicine/thorium.png");
                invTexture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/inventory/thorium.png");
            }
            healtPoint=value;
            break;
        case(medType::sp):
            string="psychic trauma.";
            points="Sanity";
            if(value<5){
                name="Antimon-Conyxa";
                texture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/medicine/antimon.png");
                invTexture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/inventory/antimon.png");
            }
            else{
                name="Oxygen-Conyxa";
                texture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/medicine/oxygen.png");
                invTexture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/inventory/oxygen.png");
            }
            sanityPoint=value;
    }
    sprite.setTexture(texture);
    num<<value;
    description="Is a medicine called\n"+name+" and\nit's use to ease your\n"+string+
                    "\n\nThis medicine can\nincrement yours "+points+"\nPoints of "+num.str()+".";

    sprite.setTextureRect(sf::IntRect(170,70,700,500));
    sprite.setScale(0.26,0.26);
    sprite.setOrigin(texture.getSize().x/2-120,texture.getSize().y/2);
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
