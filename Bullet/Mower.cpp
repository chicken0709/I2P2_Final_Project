#include <allegro5/base.h>

#include "Mower.hpp"
#include "Zombie/Zombie.hpp"
#include "Engine/Group.hpp"
#include "Scene/PlayScene.hpp"

class Plant;

Mower::Mower(Engine::Point position, Engine::Point forwardDirection, float rotation, Plant* parent) :
	Bullet("play/lawnmower.png", 300, INT16_MAX, position, forwardDirection, rotation, parent) {
	bulletType = BulletType::MOWER;
}

void Mower::OnExplode(Zombie* enemy) {
}

