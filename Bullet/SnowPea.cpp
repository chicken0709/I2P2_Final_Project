#include <allegro5/base.h>

#include "SnowPea.hpp"
#include "Zombie/Zombie.hpp"
#include "Scene/PlayScene.hpp"

class Plant;

SnowPea::SnowPea(Engine::Point position, Engine::Point forwardDirection, float rotation) :
Bullet(
    "play/snow_pea.png",
    250,
    20,
    position,
    forwardDirection,
    rotation - ALLEGRO_PI / 2
) {
    bulletType = BulletType::SNOWPEA;
}

void SnowPea::OnExplode(Zombie* zombie) {
    zombie->isSlow = true;
    zombie->UpdateSpeed();
}

