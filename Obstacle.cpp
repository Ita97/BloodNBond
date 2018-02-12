//
// Created by ita on 11/02/18.
//

#include "Obstacle.h"

Obstacle::Obstacle(ObstacleType type,int select, int x, int y):type(type),position(x,y){
    if(select>3)
        select=0;
    texture.setSmooth(true);
    switch(type){
        case ObstacleType::deadTree:
            texture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/obstacle/dead_tree.png");
            sprite.scale(1.3,1.3);
            sprite.setTextureRect(sf::IntRect(select*134,0,134,250));
            sprite.setOrigin(67,240);
            area=sf::Vector2f(30,30);
            break;
        case ObstacleType::tree:
            texture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/obstacle/tree.png");
            sprite.scale(1.5,1.5);
            sprite.setTextureRect(sf::IntRect(select*132,0,134,164));//134,164
            sprite.setOrigin(65,120);
            area=sf::Vector2f(30,30);
            break;
        case ObstacleType ::grave:
            if(select==0){//cross
                texture.loadFromFile("/home/ita/CLionProjects/BloodBond/texture/obstacle/cross.png");
                sprite.scale(0.22,0.2);
                sprite.setTextureRect(sf::IntRect(250,100,550,500));
                sprite.setOrigin(150,270);
                area=sf::Vector2f(30,30);
            }
            else if(select==1){}//grave
            else if(select==2){}//obelisc
            else if(select==3){}//tombwoof
        break;
        case ObstacleType ::forniture:
            break;
        case ObstacleType :: woodpile:
            break;

    }
    sprite.setTexture(texture);
    sprite.setPosition(x,y);
}
void Obstacle::Render(Window &window) {
    window.Draw(sprite);
}