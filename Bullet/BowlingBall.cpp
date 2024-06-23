#include "BowlingBall.hpp"
#include "Zombie/Zombie.hpp"

class Plant;

BowlingBall::BowlingBall(Engine::Point position, Engine::Point forwardDirection, float rotation, Plant* parent) :
    Bullet("play/wallnut.png", 300, INT16_MAX, position, forwardDirection, rotation, parent) {
    bulletType = BulletType::BOWLING_BALL;
    CollisionRadius = 50;
}

void BowlingBall::OnExplode(Zombie* enemy) {
}

