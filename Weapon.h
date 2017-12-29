//
// Created by ita on 14/09/17.
//

#ifndef BLOODBOND_WEAPON_H
#define BLOODBOND_WEAPON_H

#include <string>
#include <SFML/System.hpp>
#include "Window.h"


class Weapon {
protected:
    std::string name;
    sf::Time rate;
    int strength;
    std::string description;
    sf::Vector2f range;
    sf::Clock weaponClock;

public:
    explicit Weapon()= default;
    virtual ~Weapon()= default;

   const std::string &getName() const{
        return name;
    }
    virtual int use(sf::Vector2f detPosition, sf::Vector2f enemyPosition, sf::Vector2f collisionArea, int direction)=0;

    bool checkCollision(sf::Vector2f target, sf::Vector2f collisionArea,sf::Vector2f focus, sf::Vector2f range=sf::Vector2f(0,0));

    int getStrength() const {
        return strength;
    }
    void setStrength(int strength) {
        this->strength = strength;
    }

    const std::string &getDescription() const {
        return description;
    }

    void setDescription(const std::string &description) {
        this->description = description;
    }

    virtual Weapon* clone()=0;

    virtual void Render(Window &l_window)=0;

};


#endif //BLOODBOND_WEAPON_H
