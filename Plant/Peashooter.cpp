#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Bullet/BasicPea.hpp"
#include "Engine/Group.hpp"
#include "Peashooter.hpp"
#include "Scene/PlayScene.hpp"


const int Peashooter::Price = 100;

Peashooter::Peashooter(float x, float y) :
	Plant("play/peashooter.png", x, y, 10, Price, 1.5, PlantType::PEASHOOTER, "peashooter",25,71,71,{25}) {
	// Move center downward, since we the turret head is slightly biased upward.
	Anchor.y += 8.0f / GetBitmapHeight();
}

void Peashooter::CreatePea() {
	Engine::Point diff = Engine::Point(50, -35);
	// Change bullet position to the front of the gun barrel.
	getPlayScene()->BulletGroup->AddNewObject(new BasicPea(Position + diff));
	AudioHelper::PlayAudio("throw.mp3");
}
