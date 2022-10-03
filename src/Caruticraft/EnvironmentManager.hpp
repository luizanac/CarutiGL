#ifndef CARUTIGL_ENVIRONMENTMANAGER_HPP
#define CARUTIGL_ENVIRONMENTMANAGER_HPP

#include "../Core/Entity.hpp"
#include "Chunk.hpp"
#include <list>

using namespace Caruti;

namespace Caruticraft {
    const int X_MAP_SIZE = 100, Y_MAP_SIZE = 100, Z_MAP_SIZE = 100;
    const int X_CHUNK_SIZE = 25, Y_CHUNK_SIZE = 10, Z_CHUNK_SIZE = 25;

    class EnvironmentManager : public Entity {
    private:
        siv::PerlinNoise::seed_type m_Seed;
        const siv::PerlinNoise m_Perlin{m_Seed};

        std::list<Chunk *> *m_Chunks = new std::list<Chunk *>();
    public:
        explicit EnvironmentManager(siv::PerlinNoise::seed_type seed);

        void Update(const float &deltaTime) override;

        ~EnvironmentManager() override {
            delete m_Chunks;
        }
    };

}


#endif //CARUTIGL_ENVIRONMENTMANAGER_HPP
