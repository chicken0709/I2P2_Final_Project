#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "Engine/AudioHelper.hpp"
#include "Bullet/Mower.hpp"
#include "Engine/Group.hpp"
#include "LawnMower.hpp"

#include "Engine/LOG.hpp"
#include "Scene/PlayScene.hpp"


LawnMower::LawnMower(float x, float y) :
        Plant("play/gatlin_peashooter.png", x, y,6, 1000, 0, 0.3, PlantType::LAWNMOWER) {
    // Move center downward, since we the turret head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
}

void LawnMower::CreatePea() {
    Engine::LOG(Engine::INFO) << "launch mower";
    Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation));
    Engine::Point normalized = Engine::Point(50, -35);
    // Change bullet position to the front of the gun barrel.
    getPlayScene()->BulletGroup->AddNewObject(new Mower(Position + normalized, diff, 0, this));
    AudioHelper::PlayAudio("throw.mp3");
}