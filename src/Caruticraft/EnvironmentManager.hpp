#ifndef CARUTIGL_ENVIRONMENTMANAGER_HPP
#define CARUTIGL_ENVIRONMENTMANAGER_HPP

#include "../Core/Entity.hpp"
#include "Chunk.hpp"

using namespace Caruti;

namespace Caruticraft {

    class EnvironmentManager : public Entity {
    private:
        std::vector<Chunk *> *m_Chunks = new std::vector<Chunk *>();
    public:
        explicit EnvironmentManager(siv::PerlinNoise::seed_type seed);

        void Update(const float &deltaTime) override;

        ~EnvironmentManager() override {
            delete m_Chunks;
        }
    };

}


#endif //CARUTIGL_ENVIRONMENTMANAGER_HPP
