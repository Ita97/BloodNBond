//
// Created by ita on 02/10/17.
//

#include "Inventory.h"

template <typename T>
bool Inventory<T>::getElement(T el){
    if (element.size()>this->size)
        return false;
    element.push_back(el);
    return true;

}

template <typename T>
bool Inventory<T>::trowElement(T el) {
    if(element.empty())
        return false;

    for (auto it = element.begin(); it !=element.end(); it++) {
        if (el == element[it]){
            element.erase(it);
            return true;
        }
    }


}
