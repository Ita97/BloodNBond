//
// Created by ita on 20/11/17.
//

#ifndef BLOODBOND_COLDWEAPON_H
#define BLOODBOND_COLDWEAPON_H


#include "Weapon.h"

enum class coldWeaponType{knife, stick, sword};

class ColdWeapon: virtual public Weapon {
private:
    coldWeaponType c_type;
    sf::Vector2f position;
public:
    explicit ColdWeapon(coldWeaponType t);
    int use(sf::Vector2f detPosition, int direction) override;
    ColdWeapon* clone() override;
    void Render(Window &l_window) override;
    sf::Vector2f getCollisionArea() override;
    sf::Vector2f getPosition() override;
};


#endif //BLOODBOND_COLDWEAPON_H
