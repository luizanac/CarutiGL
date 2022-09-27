#ifndef CARUTIGL_TEXTURE_HPP
#define CARUTIGL_TEXTURE_HPP

#include "glad/glad.h"

class Texture {
private:
    unsigned int _id{};
    int _width{};
    int _height{};
    int _nrChannels{};
    GLenum _index;
public:
    Texture(const char *texPath, GLenum channelFormat);

    void activateAndBind(GLenum texIndex);

    [[nodiscard]] unsigned int getId() const;

    [[nodiscard]] int getWidth() const;

    [[nodiscard]] int getHeight() const;

    [[nodiscard]] int getNrChannels() const;

    [[nodiscard]] int getIndex() const;
};


#endif //CARUTIGL_TEXTURE_HPP
