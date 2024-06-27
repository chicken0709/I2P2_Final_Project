#include <string>

#include "Engine/Group.hpp"

#include "Sunflower.hpp"
#include "Sun.hpp"
#include "Scene/PlayScene.hpp"

const int Sunflower::Price = 50;

Sunflower::Sunflower(float x, float y) :
Plant(
    "sunflower",
    25,
    73,
    74,
    {25},
    x,
    y,
    10,
    Price,
    20,
    PlantType::SUNFLOWER
) {
    Anchor.y += 8.0f / GetBitmapHeight();
    reload = 10;
}

void Sunflower::CreatePea() {
    Engine::Point diff = Engine::Point(50, 20);
    getPlayScene()->BulletGroup->AddNewObject(new Sun("play/sun.png", Position + diff));
}
