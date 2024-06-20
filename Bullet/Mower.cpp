#include <allegro5/base.h>

#include "Mower.hpp"
#include "Zombie/Zombie.hpp"
#include "Engine/Group.hpp"
#include "Scene/PlayScene.hpp"

class Plant;

Mower::Mower(Engine::Point position, Engine::Point forwardDirection, float rotation, Plant* parent) :
	Bullet("play/basic_pea.png", 250, INT8_MAX, position, forwardDirection, rotation - ALLEGRO_PI / 2, parent) {
}

void Mower::OnExplode(Zombie* enemy) {
}

