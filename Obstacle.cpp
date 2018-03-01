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
    action="";
    switch(type){
        case ObstacleType::deadTree:
            texture.loadFromFile("./texture/map/obstacle/dead_tree.png");
            sprite.scale(1.3,1.3);
            sprite.setTextureRect(sf::IntRect(select*128,0,134,250));
            sprite.setOrigin(63,180);
            area=sf::Vector2f(12,10);
            collisionArea=sf::Vector2f(134,250);
            break;
        case ObstacleType::tree:
            texture.loadFromFile("./texture/map/obstacle/tree.png");
            sprite.scale(1.5,1.5);
            sprite.setTextureRect(sf::IntRect(select*132,0,134,164));//134,164
            sprite.setOrigin(65,120);
            area=sf::Vector2f(30,30);
            collisionArea=sf::Vector2f(134,164);
            break;
        case ObstacleType ::grave:
            if(select==0){//cross
                texture.loadFromFile("./texture/map/obstacle/cross.png");
                sprite.scale(0.22,0.2);
                sprite.setTextureRect(sf::IntRect(250,100,550,500));
                sprite.setOrigin(150,280);
                sprite.setColor(sf::Color(150,150,150));
                area=sf::Vector2f(30,25);
                collisionArea=sf::Vector2f(130,150);
            }
            else if(select==1){}//grave
            else if(select==2){}//obelisc
            else if(select==3){}//tombwoof
        break;
        case ObstacleType ::forniture:
            if(select==0){//table
                texture.loadFromFile("./texture/map/obstacle/table.png");
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
                texture.loadFromFile("./texture/map/obstacle/mansion_close.png");

                sprite.setOrigin(texture.getSize().x/2-115,texture.getSize().y-160);
                sprite.scale(1.3,1);
                area=sf::Vector2f(100,30);
                collisionArea=sf::Vector2f(100,100);
                action="Door unlocked!";
            }
            else if(select==1){//mansion_open
                open=true;
                texture.loadFromFile("./texture/map/obstacle/mansion_open.png");
                sprite.scale(1.3,1);
                sprite.setOrigin(texture.getSize().x/2-115,texture.getSize().y-160);
                area=sf::Vector2f(0,0);
                collisionArea=sf::Vector2f(0,0);
            }
            break;
        case ObstacleType ::box:
            if(select==0){//close
                unlockable=true;
                texture.loadFromFile("./texture/map/obstacle/box.png");
                sprite.setTextureRect(sf::IntRect(0,0,100,100));
                sprite.setOrigin(60,50);
                area=sf::Vector2f(40,30);
                collisionArea=sf::Vector2f(65,50);
            }else{//open
                open=true;
                texture.loadFromFile("./texture/map/obstacle/box.png");
                sprite.setTextureRect(sf::IntRect(118,0,100,100));
                sprite.setOrigin(60,50);
                area=sf::Vector2f(40,30);
                collisionArea=sf::Vector2f(65,50);
            }

            break;
        default:
            sprite.setTextureRect(sf::IntRect(0,0,0,0));
            area=sf::Vector2f(380,150);
            collisionArea=sf::Vector2f(0,0);
    }
        sprite.setTexture(texture);
}
void Obstacle::Render(sf::RenderWindow &window) {
    window.draw(sprite);
}
