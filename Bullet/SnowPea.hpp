#ifndef SNOWPEA_HPP
#define SNOWPEA_HPP
#include "Bullet.hpp"

class Zombie;
class Plant;
namespace Engine {
    struct Point;
}  // namespace Engine

class SnowPea : public Bullet {
public:
    explicit SnowPea(Engine::Point position, Engine::Point forwardDirection, float rotation, Plant* parent);
    void OnExplode(Zombie* enemy) override;
};
#endif // SNOWPEA_HPP
