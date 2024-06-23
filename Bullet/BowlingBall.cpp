#include "BowlingBall.hpp"

#include "Engine/LOG.hpp"
#include "Zombie/Zombie.hpp"

class Plant;

BowlingBall::BowlingBall(int idx,Engine::Point position, Engine::Point forwardDirection, float rotation, Plant* parent) :
    Bullet(idx,13,71,71 ,"play/basic_zombie.png",300, INT16_MAX, position, forwardDirection, rotation, parent) {
    Engine::LOG(Engine::INFO) << "Adding new bowling";
    bulletType = BulletType::BOWLING_BALL;
    CollisionRadius = 50;
}

void BowlingBall::OnExplode(Zombie* enemy) {
}

