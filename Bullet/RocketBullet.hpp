#ifndef ROCKETBULLET_HPP
#define ROCKETBULLET_HPP
#include "Bullet.hpp"

class Zombie;
class Plant;
namespace Engine {
    struct Point;
}  // namespace Engine

class RocketBullet : public Bullet {
public:
    explicit RocketBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Plant* parent);
    void OnExplode(Zombie* enemy) override;
};
#endif // ROCKETBULLET_HPP