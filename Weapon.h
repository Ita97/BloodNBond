//
// Created by ita on 14/09/17.
//

#ifndef BLOODBOND_WEAPON_H
#define BLOODBOND_WEAPON_H
#include <string>
enum class  weaponType{ stick, knife, pickAxe, spade, axe, gun, shotGun, rifle, unknown };

class Weapon {
private:
    int strength;
    int durability;
    weaponType type;
    std::string description;

public:
    Weapon()=default;
    Weapon(int s, int d, weaponType t): strength(s), durability(d), type(t){};

    int getStrength() const {
        return strength;
    }

    void setStrength(int strenght) {
        Weapon::strength = strenght;
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
