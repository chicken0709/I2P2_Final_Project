#ifndef BOMBBOWLINGBALL_HPP
#define BOMBBOWLINGBALL_HPP
#include "Bullet.hpp"

class Zombie;
class Plant;
namespace Engine {
    struct Point;
}  // namespace Engine

class BombBowlingBall : public Bullet {
public:
    explicit BombBowlingBall(int index, Engine::Point position, Engine::Point forwardDirection, float rotation, Plant* parent);
    void OnExplode(Zombie* enemy) override;
};
#endif // BOMBBOWLINGBALL_HPP
