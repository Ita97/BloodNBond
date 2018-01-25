//
// Created by ita on 04/10/17.
//

#ifndef BLOODBOND_MEDICINE_H
#define BLOODBOND_MEDICINE_H

#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

enum class medType{hp,sp};

class Medicine {
public:
    explicit Medicine(int value, medType type);

    bool isPsichic(){
        return type == medType::sp;
    }
    bool isPhisical(){
        return type == medType::hp;
    }
    const std::string& getDescription(){
        return description;
    }
    const std::string &getName() const{
        return name;
    }
    int getHP() const {
        return healtPoint;
    }

    int getSanityPoint() const {
        return sanityPoint;
    }

    bool operator==(const Medicine& right );

    sf::Sprite& getSprite(){
        return sprite;
    }
    const sf::Texture& getInventoryTexture(){
        return invTexture;
    }
    bool use(){
        return true;
    }
private:
    std::string name, description;
    int healtPoint;
    int sanityPoint;
    medType type;
    sf::Texture texture,invTexture;
    sf::Sprite sprite;
};



#endif //BLOODBOND_MEDICINE_H
