#include "Mower.hpp"
#include "Zombie/Zombie.hpp"

class Plant;

Mower::Mower(Engine::Point position) :
Bullet(
	"play/lawnmower.png",
	300,
	INT16_MAX,
	position
) {
	bulletType = BulletType::MOWER;
    CollisionRadius = 50;
}

void Mower::OnExplode(Zombie* enemy) {
}

