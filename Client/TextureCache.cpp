#include "TextureCache.h"
#include "ImageLoader.h"

GLTexture TextureCache::getTexture(std::string texturePath) {
    // std::map<std::string, GLTexture>::iterator <==> auto
    // lookup for texture and see if it's in the map
    auto mapIterator =  textureMap.find(texturePath);

    // check if it isn't in the map
    if (mapIterator == textureMap.end()) {
        // load the texture
        GLTexture texture = ImageLoader::loadTexture(texturePath);

        // create new pair for the map
        //std::pair<std::string, GLTexture> pair(texturePath, texture);

        // insert new texture into the map, shortcut
        textureMap.insert(std::make_pair(texturePath, texture));
        return texture;
    }

    // first - key
    // second - value
    return mapIterator->second;
}
