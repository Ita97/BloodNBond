//
// Created by ciape on 19/11/17.
//

#ifndef B_B_TEXTUREMANAGER_H
#define B_B_TEXTUREMANAGER_H



#include <SFML/Graphics.hpp>
#include <string>
#include <map>


class TextureManager
{
private:

    /* Array of textures used */
    std::map<std::string, sf::Texture> textures;

public:

    /* Add a texture from a file */
    void loadTexture(const std::string& name, const std::string &filename);

    /* Translate an id into a reference */
    sf::Texture& getRef(const std::string& texture);

    /* Constructor */
    TextureManager()
    {
    }
};


#endif //B_B_TEXTUREMANAGER_H
