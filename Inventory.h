//
// Created by ita on 02/10/17.
//

#ifndef BLOODBOND_INVENTORY_H
#define BLOODBOND_INVENTORY_H


#include <vector>
#include <algorithm>

template <typename T>

class Inventory {
private:
    int size;
    std::vector<T> element;
    //todo se vuoi aggiungi categoria..

public:
    explicit Inventory(int size, std:: vector<T> chest={}):
            size(size), element(chest){
    }
    ~Inventory(){
        std::vector<T>::~vector();
    }

    int getSize() const{
        return size;
    }
    void setSize(int s){
        Inventory::size=s;
    }
    bool getElement(T el);
    bool trowElement(T el);
};


#endif //BLOODBOND_INVENTORY_H
