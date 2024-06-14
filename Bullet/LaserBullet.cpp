#include <allegro5/base.h>
#include <random>
#include <string>

#include "UI/Animation/DirtyEffect.hpp"
#include "Zombie/Zombie.hpp"
#include "Engine/Group.hpp"
#include "LaserBullet.hpp"
#include "Scene/PlayScene.hpp"
#include "Engine/Point.hpp"

class Plant;

LaserBullet::LaserBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Plant* parent) :
	Bullet("play/bullet-2.png", 800, 2, position, forwardDirection, rotation - ALLEGRO_PI / 2, parent) {
}
void LaserBullet::OnExplode(Zombie* enemy) {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> dist(2, 10);
	getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/dirty-2.png", dist(rng), enemy->Position.x, enemy->Position.y));
}
