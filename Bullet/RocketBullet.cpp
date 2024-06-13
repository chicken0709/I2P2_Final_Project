#include <allegro5/base.h>
#include <random>
#include <string>

#include "UI/Animation/DirtyEffect.hpp"
#include "Zombie/Zombie.hpp"
#include "Engine/Group.hpp"
#include "RocketBullet.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"

class Plant;

RocketBullet::RocketBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Plant* parent) :
        Bullet("play/bullet-11.png", 600, 10, position, forwardDirection, rotation - ALLEGRO_PI / 2, parent) {
}

void RocketBullet::OnExplode(Zombie* enemy) {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(2, 10);
    getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/dirty-3.png", dist(rng), enemy->Position.x, enemy->Position.y));
    enemy->UpdateSpeed();
}
