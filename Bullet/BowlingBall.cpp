#include "Engine/Resources.hpp"

#include "BowlingBall.hpp"
#include "Zombie/Zombie.hpp"

class Plant;

BowlingBall::BowlingBall(std::string name, Engine::Point position, Engine::Point forwardDirection, float rotation) :
Bullet(
    name,
    13,
    71,
    71 ,
    300,
    INT16_MAX,
    position,
    forwardDirection,
    rotation
) {
    spriteSheet = Engine::Resources::GetInstance().GetBitmap("play/" + name + "_animation_1.png");
    bulletType = BulletType::BOWLING_BALL;
    CollisionRadius = 50;
}

void BowlingBall::OnExplode(Zombie* enemy) {
}

