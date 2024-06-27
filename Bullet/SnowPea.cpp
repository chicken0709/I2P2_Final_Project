#include <allegro5/base.h>

#include "SnowPea.hpp"
#include "Zombie/Zombie.hpp"
#include "Scene/PlayScene.hpp"

class Plant;

SnowPea::SnowPea(Engine::Point position) :
Bullet(
    "play/snow_pea.png",
    250,
    20,
    position
) {
    bulletType = BulletType::SNOWPEA;
}

void SnowPea::OnExplode(Zombie* zombie) {
    zombie->isSlow = true;
    zombie->UpdateSpeed();
}

