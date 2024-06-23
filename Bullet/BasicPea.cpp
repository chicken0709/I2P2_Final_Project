#include <allegro5/base.h>

#include "BasicPea.hpp"
#include "Zombie/Zombie.hpp"

class Plant;

BasicPea::BasicPea(Engine::Point position, Engine::Point forwardDirection, float rotation, Plant* parent) :
	Bullet("play/basic_pea.png", 250, 200, position, forwardDirection, rotation - ALLEGRO_PI / 2, parent) {
    bulletType = BulletType::BASICPEA;
}

void BasicPea::OnExplode(Zombie* enemy) {
}

