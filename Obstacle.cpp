//
// Created by ita on 11/02/18.
//

#include "Obstacle.h"

Obstacle::Obstacle(ObstacleType type,int select):type(type){
    if(select>3)
        select=0;
    open=false;
    unlockable=false;
    texture.setSmooth(true);
    lock=keyType::null;
    switch(type){
        case ObstacleType::deadTree:
            texture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/obstacle/dead_tree.png");
            sprite.scale(1.3,1.3);
            sprite.setTextureRect(sf::IntRect(select*128,0,134,250));
            sprite.setOrigin(63,188);
            area=sf::Vector2f(12,6);
            collisionArea=sf::Vector2f(134,250);
            break;
        case ObstacleType::tree:
            texture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/obstacle/tree.png");
            sprite.scale(1.5,1.5);
            sprite.setTextureRect(sf::IntRect(select*132,0,134,164));//134,164
            sprite.setOrigin(65,120);
            area=sf::Vector2f(30,30);
            collisionArea=sf::Vector2f(134,164);
            break;
        case ObstacleType ::grave:
            if(select==0){//cross
                texture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/obstacle/cross.png");
                sprite.scale(0.22,0.2);
                sprite.setTextureRect(sf::IntRect(250,100,550,500));
                sprite.setOrigin(150,275);
                sprite.setColor(sf::Color(150,150,150));
                area=sf::Vector2f(30,25);
                collisionArea=sf::Vector2f(130,200);
            }
            else if(select==1){}//grave
            else if(select==2){}//obelisc
            else if(select==3){}//tombwoof
        break;
        case ObstacleType ::forniture:
            if(select==0){//table
                texture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/obstacle/table.png");
                sprite.scale(0.4,0.4);
                sprite.setOrigin(texture.getSize().x/2,texture.getSize().y/2+30);
                area=sf::Vector2f(100,40);
                collisionArea=sf::Vector2f(200,300);
            }
            break;
        case ObstacleType :: woodpile:
            break;



        case ObstacleType ::building:

            if(select==0){//mansion_close
                unlockable=true;
                lock=keyType ::skeleton;
                texture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/obstacle/mansion_close.png");

                sprite.setOrigin(texture.getSize().x/2-115,texture.getSize().y-160);
                sprite.scale(1.3,1);
                area=sf::Vector2f(100,30);
                collisionArea=sf::Vector2f(100,100);
            }
            else if(select==1){//mansion_open
                open=true;
                texture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/obstacle/mansion_open.png");
                sprite.scale(1.3,1);
                sprite.setOrigin(texture.getSize().x/2-115,texture.getSize().y-160);
                area=sf::Vector2f(0,0);
                collisionArea=sf::Vector2f(0,0);
            }
            break;
        default:
            sprite.setTextureRect(sf::IntRect(0,0,0,0));
            area=sf::Vector2f(380,150);
            collisionArea=sf::Vector2f(0,0);
    }
        sprite.setTexture(texture);
}
void Obstacle::Render(Window &window) {
    window.Draw(sprite);
}