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
    explicit BombBowlingBall(std::string name, Engine::Point position, Engine::Point forwardDirection, float rotation);
    void OnExplode(Zombie* enemy) override;
};
#endif // BOMBBOWLINGBALL_HPP
