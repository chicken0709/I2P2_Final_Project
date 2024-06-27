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
    explicit BowlingBall(std::string name, Engine::Point position, Engine::Point forwardDirection, float rotation);
    void OnExplode(Zombie* enemy) override;
};
#endif // BOWLINGBALL_HPP
