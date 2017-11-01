//
// Created by ita on 14/09/17.
//

#ifndef BLOODBOND_DETECTIVE_H
#define BLOODBOND_DETECTIVE_H

#include <string>
#include "Character.h"
#include "Tools.h"
#include "Inventory.h"
#include "Medicine.h"
#include <SFML/Graphics.hpp>

class Detective: virtual public Character {
public:
    Detective(int h, int x, int y, Weapon* w, std::string det, int sp, int ap);//, Tools* t=nullptr);
    ~Detective(){
      //  delete[] weapon;
      //  delete[] tool;
    }

    virtual void move(int x, int y) override;
    virtual void attack() override;

    //void use(Tools* t);
    int getSanity() const;
    void setSanity(int sp);
    int getAbilityPoint() const;
    void setAbilityPoint(int ap);
    void openInventory();
    void closeInventory();

private:
    std::string name;
    int sanityPoint;
    int abilityPoint;
    sf::Sprite detective;
    bool inventoryState;
    //Inventory* inventory;
    //Tools* tool;

};


#endif //BLOODBOND_DETECTIVE_H
