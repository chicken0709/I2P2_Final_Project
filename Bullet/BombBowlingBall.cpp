#include "Engine/AudioHelper.hpp"

#include "BombBowlingBall.hpp"
#include "Zombie/Zombie.hpp"
#include "Scene/PlayScene.hpp"

class Plant;

BombBowlingBall::BombBowlingBall(int index, Engine::Point position, Engine::Point forwardDirection, float rotation, Plant* parent) :
Bullet(
    index,
    8,
    71,
    71,
    "play/basic_zombie.png",
    300,
    INT16_MAX,
    position,
    forwardDirection,
    rotation,
    parent
) {
    bulletType = BulletType::BOMB_BOWLING_BALL;
    CollisionRadius = 50;
}

void BombBowlingBall::OnExplode(Zombie* enemy) {
    AudioHelper::PlayAudio("cherrybomb.ogg");
    for (auto& it : getPlayScene()->EnemyGroup->GetObjects()) {
        Zombie* zombie = dynamic_cast<Zombie*>(it);
        if((zombie->Position - Position).Magnitude() < 225)
            zombie->TakeDamage(INT16_MAX);
    }
}

