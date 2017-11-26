//
// Created by ita on 14/09/17.
//

#ifndef BLOODBOND_DETECTIVE_H
#define BLOODBOND_DETECTIVE_H

#include <string>
#include "Character.h"
#include "Enemy.h"
#include "Inventory.h"
#include "Medicine.h"
#include "Window.h"
#include <SFML/Graphics.hpp>


class Detective: virtual public Character {
public:
    Detective( const std::string& det,int h, int sp, int ap, int x, int y, Weapon* w);
    Detective(const Detective &original);
    Detective& operator =(const Detective &right);

    void move() override;
    void attack(Character& enemy) override;


    int getSanity() const{
        return sanityPoint;
    }
    void setSanity(int sp){
        sanityPoint+=sp;
    };
    int getAbilityPoint() const{
        return abilityPoint;
    }
    void setAbilityPoint(int ap){
        abilityPoint=ap;
    }
    void openInventory();
    void closeInventory();
    void useMedicine(Medicine medication);


private:
    std::string name;
    int sanityPoint;
    int abilityPoint;
    bool inventoryState;



};


#endif //BLOODBOND_DETECTIVE_H
