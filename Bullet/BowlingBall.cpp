#include "BowlingBall.hpp"
#include "Zombie/Zombie.hpp"

class Plant;

BowlingBall::BowlingBall(int index, Engine::Point position, Engine::Point forwardDirection, float rotation, Plant* parent) :
Bullet(
    index,
    13,
    71,
    71 ,
    "play/basic_zombie.png",
    300,
    INT16_MAX,
    position,
    forwardDirection,
    rotation, parent
) {
    bulletType = BulletType::BOWLING_BALL;
    CollisionRadius = 50;
}

void BowlingBall::OnExplode(Zombie* enemy) {
}

