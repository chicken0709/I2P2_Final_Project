#ifndef FIREPEA_HPP
#define FIREPEA_HPP
#include "Bullet.hpp"

class Zombie;
class Plant;
namespace Engine {
    struct Point;
}  // namespace Engine

class FirePea : public Bullet {
public:
    explicit FirePea(Engine::Point position, Engine::Point forwardDirection, float rotation, Plant* parent);
    void OnExplode(Zombie* enemy) override;
};
#endif // FIREPEA_HPP
