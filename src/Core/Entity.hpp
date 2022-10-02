#ifndef CARUTIGL_ENTITY_HPP
#define CARUTIGL_ENTITY_HPP

#include "glm/glm.hpp"

namespace Caruti {


    using namespace glm;

    class Entity {
    public:
        vec3 m_Position = vec3(0, 0, 0);
        vec3 m_Rotation = vec3(0, 0, 0);
        vec3 m_Scale = vec3(0, 0, 0);

    protected:

    public:

        virtual void Update(const float &deltaTime) = 0;

        Entity() = default;

        virtual ~Entity() = default;
    };

} // Caruti

#endif //CARUTIGL_ENTITY_HPP
