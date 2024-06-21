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
	Plant("play/peashooter.png", x, y, 10, Price, 1.5, PlantType::PEASHOOTER) {
	// Move center downward, since we the turret head is slightly biased upward.
	Anchor.y += 8.0f / GetBitmapHeight();
}

void Peashooter::CreatePea() {
	Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation));
	Engine::Point normalized = Engine::Point(50, -35);
	// Change bullet position to the front of the gun barrel.
	getPlayScene()->BulletGroup->AddNewObject(new BasicPea(Position + normalized, diff, 0, this));
	AudioHelper::PlayAudio("throw.mp3");
}
