//
// Created by ita on 14/09/17.
//

#ifndef BLOODBOND_DETECTIVE_H
#define BLOODBOND_DETECTIVE_H

#include <string>
#include "Character.h"

#include "Inventory.h"
#include "Medicine.h"
#include "Window.h"
#include <SFML/Graphics.hpp>

class Detective: virtual public Character {
public:
    Detective(int h, int x, int y, Weapon* w, std::string det, int sp, int ap);
    Detective(const Detective &original);
    Detective& operator =(const Detective &right);

    void move() override;
    void attack() override;

    void Render(Window& l_window) override;

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
    void use(Medicine medication);

private:
    std::string name;
    int sanityPoint;
    int abilityPoint;
    sf::Sprite detective;
    sf::Texture t_det;
    float frame=0;
    bool inventoryState;
    //Inventory* inventory;


};


#endif //BLOODBOND_DETECTIVE_H
