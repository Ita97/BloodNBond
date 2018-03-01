//
// Created by ita on 14/09/17.
//
#include "Weapon.h"

bool Weapon::checkCollision(sf::Vector2f target, sf::Vector2f collisionArea,sf::Vector2f focus, sf::Vector2f range) {
    if(focus.x+range.x>target.x-collisionArea.x && focus.x-range.x<target.x+collisionArea.x)
        if(focus.y+range.y>target.y-collisionArea.y && focus.y-range.y<target.y+ collisionArea.y)
        return true;
    return false;

}

const sf::Texture& Weapon::getTexture(){
    return texture;
}

void Weapon::getTextureDetails(sf::Vector2i &size, sf::Vector2i &distance, int &frameNumber) {
    size=textureSize;
    distance=frameDistance;
    frameNumber=frameCount;
}
