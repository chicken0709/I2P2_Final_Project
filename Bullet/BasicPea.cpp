#include <allegro5/base.h>
#include <random>
#include <string>

#include "BasicPea.hpp"
#include "UI/Animation/DirtyEffect.hpp"
#include "Zombie/Zombie.hpp"
#include "Engine/Group.hpp"
#include "Scene/PlayScene.hpp"

class Plant;

BasicPea::BasicPea(Engine::Point position, Engine::Point forwardDirection, float rotation, Plant* parent) :
	Bullet("play/basic_pea.png", 250, 1, position, forwardDirection, rotation - ALLEGRO_PI / 2, parent) {
}
void BasicPea::OnExplode(Zombie* enemy) {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(2, 5);
	getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/dirty-1.png", dist(rng), enemy->Position.x, enemy->Position.y));
}

