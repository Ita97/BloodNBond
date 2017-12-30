//
// Created by ita on 04/10/17.
//
#include "Medicine.h"

Medicine::Medicine(int value, medType type) : type(type){
    if(value>6)
        name="Super-";
    else if(value<3)
        name="Weak-";
    else
        name="";
    switch(this->type){
        case (medType ::hp):
            name=name+"Potion";
            healtPoint=value;
            break;
        case(medType::sp):
            name=name+"Elixir";
            sanityPoint=value;
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
