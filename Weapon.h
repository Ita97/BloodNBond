//
// Created by ita on 14/09/17.
//

#ifndef BLOODBOND_WEAPON_H
#define BLOODBOND_WEAPON_H
#include <string>
enum class  weaponType{ stick, knife, pickAxe, spade, axe, gun, shotGun, rifle };

class Weapon {
private:
    int strenght;
    int durability;
    weaponType type;
    std::string description;

public:
    Weapon(int s, int d, weaponType t): strenght(s), durability(d), type(t){};

    int getStrenght() const {
        return strenght;
    }

    void setStrenght(int strenght) {
        Weapon::strenght = strenght;
    }

    int getDurability() const {
        return durability;
    }

    void setDurability(int durability) {
        Weapon::durability = durability;
    }

    const std::string &getDescription() const {
        return description;
    }

    void setDescription(const std::string &description) {
        Weapon::description = description;
    }

    Weapon* clone() const{
        return new Weapon(*this);
    }

};


#endif //BLOODBOND_WEAPON_H
