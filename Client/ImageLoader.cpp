#include "ImageLoader.h"
#include "PicoPNG.H"
#include "IOManager.h"
#include "SDLException.h"

GLTexture ImageLoader::loadTexture(std::string filePath) {
    // initialize struct components to 0 (use {})
    GLTexture texture;

    // output vector to be filled
    std::vector<unsigned char> out;
    // input data
    std::vector<unsigned char> in;

    // image props
    unsigned long width;
    unsigned long height;

    // read data to input buffer
    if (IOManager::readFileToBuffer(filePath, in) == false) {
        throw SDLException("Failed to read PNG file to buffer.");
    }

    int errorCode = decodePNG(out, width, height, &(in[0]), in.size());

    // check for errors
    if (errorCode != 0) {
        throw SDLException("Decode PNG failed with error: " + std::to_string(errorCode));
    }

    // set width, height of texture
    texture.width = width;
    texture.height = height;

    // generate texture object
    glGenTextures(1, &(texture.ID));

    // bind texture
    glBindTexture(GL_TEXTURE_2D, texture.ID);

    // upload image data to texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &(out[0]));

    // some texture params (wtf xd)
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    // generate mipmap based on upper parameters
    glGenerateMipmap(GL_TEXTURE_2D);

    // unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}
