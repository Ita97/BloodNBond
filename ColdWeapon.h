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
    ~ColdWeapon() override = default;
    int startAttack(sf::Vector2f detPosition, int direction) override;
    void use() override;
    ColdWeapon* clone() override;
    void Render(sf::RenderWindow &l_window) override;
    sf::Vector2f getCollisionArea() override;
    sf::Vector2f getPosition() override;
};


#endif //BLOODBOND_COLDWEAPON_H
