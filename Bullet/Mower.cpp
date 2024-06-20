#include <allegro5/base.h>

#include "Mower.hpp"
#include "Zombie/Zombie.hpp"
#include "Engine/Group.hpp"
#include "Scene/PlayScene.hpp"

class Plant;

Mower::Mower(Engine::Point position, Engine::Point forwardDirection, float rotation, Plant* parent) :
	Bullet("play/basic_pea.png", 125, INT8_MAX, position, forwardDirection, rotation - ALLEGRO_PI / 2, parent) {
	bullettype = Bullettype::MOWER;
}

void Mower::OnExplode(Zombie* enemy) {
}

