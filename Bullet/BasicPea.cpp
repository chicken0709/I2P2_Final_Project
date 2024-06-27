#include <allegro5/base.h>

#include "BasicPea.hpp"
#include "Zombie/Zombie.hpp"

class Plant;

BasicPea::BasicPea(Engine::Point position) :
Bullet(
    "play/basic_pea.png",
    250,
    20,
    position
) {
    bulletType = BulletType::BASICPEA;
}

void BasicPea::OnExplode(Zombie* enemy) {
}

