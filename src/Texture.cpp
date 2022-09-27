#include <iostream>
#include <vector>
#include "Texture.hpp"
#include "stb_image.h"
#include "fmt/core.h"

Texture::Texture(const char *texPath, GLenum channelFormat) {
    stbi_set_flip_vertically_on_load(true);
    glGenTextures(1, &_id);
    glBindTexture(GL_TEXTURE_2D, _id);

    //TODO: Create a function to configure texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char *buffer = stbi_load(
            texPath,
            &_width, &_height,
            &_nrChannels, 0);

    if (buffer) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, channelFormat, GL_UNSIGNED_BYTE, buffer);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << fmt::format("Failed to load texture: {}", texPath) << std::endl;
    }
    stbi_image_free(buffer);
}

void Texture::activateAndBind(GLenum texIndex) {
    _index = texIndex;
    glActiveTexture(_index);
    glBindTexture(GL_TEXTURE_2D, _id);
}

unsigned int Texture::getId() const {
    return _id;
}

int Texture::getWidth() const {
    return _width;
}

int Texture::getHeight() const {
    return _height;
}

int Texture::getNrChannels() const {
    return _nrChannels;
}

int Texture::getIndex() const {

    switch (_index) {
        case GL_TEXTURE0:
            return 0;
        case GL_TEXTURE1:
            return 1;
        case GL_TEXTURE2:
            return 2;
        case GL_TEXTURE3:
            return 3;
        case GL_TEXTURE4:
            return 4;
        case GL_TEXTURE5:
            return 5;
        case GL_TEXTURE6:
            return 6;
    }

    return -1;
}

