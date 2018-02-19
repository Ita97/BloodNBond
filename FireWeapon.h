//
// Created by ita on 20/11/17.
//

#ifndef BLOODBOND_FIREWEAPON_H
#define BLOODBOND_FIREWEAPON_H

#include <SFML/Graphics/RectangleShape.hpp>
#include "Weapon.h"
#include "Bullet.h"
#include <vector>

enum class fireWeaponType{ rifle, gun, shotGun};

class FireWeapon: virtual public Weapon {

private:

    int ammoMax; //munizioni
    int cartridge;
    float shotSpeed;
    Bullet* bullet;
    std::vector<Bullet*> shotBullets;
    fireWeaponType f_type;
    sf::Vector2f bulletSize;
    int num;

public:
    explicit FireWeapon(fireWeaponType t);
    int startAttack(sf::Vector2f detPosition, int direction) override;
    void use() override;
    FireWeapon* clone() override;
    void reloadCartridge(int ammo);
    bool isInsideRange(sf::Vector2f focus,sf::Vector2f target);
    void Render(Window &l_window) override;
    sf::Vector2f getCollisionArea() override;
    sf::Vector2f getPosition() override;
};



#endif //BLOODBOND_FIREWEAPON_H
