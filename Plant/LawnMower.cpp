#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Bullet/Mower.hpp"
#include "Engine/Group.hpp"
#include "LawnMower.hpp"

#include "Scene/PlayScene.hpp"


LawnMower::LawnMower(float x, float y) :
        Plant("play/gatlin_peashooter.png", x, y,6, 1000, 0, 0.3, PlantType::PEASHOOTER) {
    // Move center downward, since we the turret head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
}

void PlayScene::CreateLawnMower(Engine::Point position) {
    Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation));
    Engine::Point normalized = Engine::Point(50, -35);
    // Change bullet position to the front of the gun barrel.
    BulletGroup->AddNewObject(new LawnMower(position + normalized, diff, 0, this));
    AudioHelper::PlayAudio("throw.mp3");
}