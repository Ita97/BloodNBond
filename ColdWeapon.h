//
// Created by ita on 20/11/17.
//

#ifndef BLOODBOND_COLDWEAPON_H
#define BLOODBOND_COLDWEAPON_H

#include "Weapon.h"

enum class coldWeaponType{knife, stick, axe};

class ColdWeapon: virtual public Weapon {
private:
    coldWeaponType c_type;
public:
    explicit ColdWeapon(coldWeaponType t);
    int use(sf::Vector2f detPosition, sf::Vector2f enemyPosition, sf::Vector2f collisionArea, int direction) override;
    ColdWeapon* clone() override;
    void Render(Window &l_window) override;
};


#endif //BLOODBOND_COLDWEAPON_H
