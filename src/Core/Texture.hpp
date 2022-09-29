#ifndef CARUTIGL_TEXTURE_HPP
#define CARUTIGL_TEXTURE_HPP

#include "glad/glad.h"

namespace Caruti {
    class Texture {
    private:
        unsigned int _id{};
        int _width{};
        int _height{};
        int _nrChannels{};
        GLenum _index;
    public:
        Texture(const char *texPath, GLenum channelFormat);

        void ActivateAndBind(GLenum texIndex);

        [[nodiscard]] unsigned int GetId() const;

        [[nodiscard]] int GetWidth() const;

        [[nodiscard]] int GetHeight() const;

        [[nodiscard]] int GetNrChannels() const;

        [[nodiscard]] int GetIndex() const;
    };
}

#endif //CARUTIGL_TEXTURE_HPP
