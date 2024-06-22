#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Bullet/SnowPea.hpp"
#include "Engine/Group.hpp"
#include "SnowPeashooter.hpp"
#include "Scene/PlayScene.hpp"

const int SnowPeashooter::Price = 175;

SnowPeashooter::SnowPeashooter(float x, float y) :
        Plant("play/snow_peashooter.png", x, y, 10, Price, 1.5, PlantType::PEASHOOTER,"snowpeashooter",25,71,71) {
    // Move center downward, since we the turret head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
}

void SnowPeashooter::CreatePea() {
    Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation));
    Engine::Point normalized = Engine::Point(50, -35);
    // Change bullet position to the front of the gun barrel.
    getPlayScene()->BulletGroup->AddNewObject(new SnowPea(Position + normalized, diff, 0, this));
    AudioHelper::PlayAudio("snow_pea_sparkles.ogg");
}
