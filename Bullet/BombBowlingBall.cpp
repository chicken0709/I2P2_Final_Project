#include "Engine/AudioHelper.hpp"
#include "Engine/Resources.hpp"

#include "BombBowlingBall.hpp"
#include "Zombie/Zombie.hpp"
#include "Scene/PlayScene.hpp"

class Plant;

BombBowlingBall::BombBowlingBall(std::string name, Engine::Point position, Engine::Point forwardDirection, float rotation) :
Bullet(
    name,
    8,
    71,
    71,
    300,
    INT16_MAX,
    position,
    forwardDirection,
    rotation
) {
    spriteSheet = Engine::Resources::GetInstance().GetBitmap("play/" + name + "_animation_1.png");
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

