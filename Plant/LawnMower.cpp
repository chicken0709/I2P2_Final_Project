#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"

#include "LawnMower.hpp"
#include "Bullet/Mower.hpp"
#include "Scene/PlayScene.hpp"

LawnMower::LawnMower(float x, float y) :
Plant(
    "lawnmower",
    "play/lawnmower.png",
    x,
    y,
    0,
    0,
    0,
    PlantType::LAWNMOWER
) {
    Anchor.y += 8.0f / GetBitmapHeight();
}

void LawnMower::CreatePea() {
    AudioHelper::PlayAudio("lawnmower.ogg");
    getPlayScene()->BulletGroup->AddNewObject(new Mower(Position));
}