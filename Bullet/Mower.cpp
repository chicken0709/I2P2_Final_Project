#include "Mower.hpp"
#include "Zombie/Zombie.hpp"

class Plant;

Mower::Mower(Engine::Point position, Engine::Point forwardDirection, float rotation, Plant* parent) :
Bullet(
	"play/lawnmower.png",
	300,
	INT16_MAX,
	position,
	forwardDirection,
	rotation,
	parent
) {
	bulletType = BulletType::MOWER;
    CollisionRadius = 50;
}

void Mower::OnExplode(Zombie* enemy) {
}

