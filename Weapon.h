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
    sf::Texture texture;
    sf::Vector2i frameDistance,textureSize;
    int frameCount;
    bool hit;

public:
    explicit Weapon()= default;
    virtual ~Weapon()= default;

    virtual sf::Vector2f getCollisionArea()=0;
   const std::string &getName() const{
        return name;
    }
    virtual void use()=0;
    virtual int startAttack(sf::Vector2f detPosition, int direction)=0;
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

    virtual const sf::Texture& getTexture();
    void getTextureDetails(sf::Vector2i& size, sf::Vector2i& distance, int& frameNumber){
        size=textureSize;
        distance=frameDistance;
        frameNumber=frameCount;
    }
    virtual sf::Vector2f getPosition()=0;
    sf::Vector2f getRange(){
        return range;
    }
};


#endif //BLOODBOND_WEAPON_H
