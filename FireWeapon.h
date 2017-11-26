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
    std::vector<Bullet> cartridge; //caricatore
    fireWeaponType f_type;

public:
    explicit FireWeapon(fireWeaponType t);
    ~FireWeapon(){}
    int use(sf::Vector2f detPosition, sf::Vector2f enemyPosition, sf::Vector2f collisionArea, int direction) override;
    FireWeapon* clone() override;
    void reloadCartridge(sf::Vector2f bulletSize, int ammo);

    void Render(Window &l_window) override;
};



#endif //BLOODBOND_FIREWEAPON_H
