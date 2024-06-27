#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"

#include "SnowPeashooter.hpp"
#include "Bullet/SnowPea.hpp"
#include "Scene/PlayScene.hpp"

const int SnowPeashooter::Price = 175;

SnowPeashooter::SnowPeashooter(float x, float y) :
Plant(
    "snowpeashooter",
    25,
    71,
    71,
    {25},
    x,
    y,
    10,
    Price,
    1.5
) {
    plantType = PlantType::PEASHOOTER;
    Anchor.y += 8.0f / GetBitmapHeight();
}

void SnowPeashooter::CreatePea() {
    Engine::Point diff = Engine::Point(50, -35);
    getPlayScene()->BulletGroup->AddNewObject(new SnowPea(Position + diff));
    AudioHelper::PlayAudio("snow_pea_sparkles.ogg");
}
