//
// Created by ciape on 19/11/17.
//

#include "TextureManager.h"





void TextureManager::loadTexture(const std::string& name, const std::string& filename)
{
    /* Load the texture */
    sf::Texture tex;
    tex.loadFromFile(filename);

    /* Add it to the list of textures */
    this->textures[name] = tex;


}

sf::Texture& TextureManager::getRef(const std::string& texture)
{
    return this->textures.at(texture);
}