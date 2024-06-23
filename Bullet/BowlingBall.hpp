#ifndef BOWLINGBALL_HPP
#define BOWLINGBALL_HPP
#include "Bullet.hpp"

class Zombie;
class Plant;
namespace Engine {
    struct Point;
}  // namespace Engine

class BowlingBall : public Bullet {
public:
    explicit BowlingBall(Engine::Point position, Engine::Point forwardDirection, float rotation, Plant* parent);
    void OnExplode(Zombie* enemy) override;
};
#endif // BOWLINGBALL_HPP
