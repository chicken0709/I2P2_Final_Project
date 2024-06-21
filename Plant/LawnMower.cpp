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
        Plant("play/lawnmower.png", x, y, 0, 0, 0, PlantType::LAWNMOWER,"lawnmower") {
    Anchor.y += 8.0f / GetBitmapHeight();
}

void LawnMower::CreatePea() {
    Engine::LOG(Engine::INFO) << "launch mower";
    AudioHelper::PlayAudio("lawnmower.ogg");
    Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation));
    getPlayScene()->BulletGroup->AddNewObject(new Mower(Position, diff, 0, this));
}