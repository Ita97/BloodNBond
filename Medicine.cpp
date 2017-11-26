//
// Created by ita on 04/10/17.
//
#include "Medicine.h"

Medicine::Medicine(int value, medType type) : type(type){
    switch(this->type){
        case (medType ::hp):
            healtPoint=value;
            break;
        case(medType::sp):
            sanityPoint=value;
    }
}
