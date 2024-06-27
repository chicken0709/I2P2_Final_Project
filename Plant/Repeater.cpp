#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"

#include "Repeater.hpp"
#include "Bullet/BasicPea.hpp"
#include "Scene/PlayScene.hpp"

const int Repeater::Price = 200;

Repeater::Repeater(float x, float y) :
Plant(
    "play/repeater.png",
    x, y,
    10,
    Price,
    0.3,
    PlantType::PEASHOOTER,
    "repeater",
    25,
    73,
    71,
    {25}
) {
    Anchor.y += 8.0f / GetBitmapHeight();
}

void Repeater::CreatePea() {
    if(shotCycle == 2) {
        coolDown = 0.3;
        shotCycle = 0;
        return;
    }
    if(shotCycle == 1) {
        coolDown = 0.9;
        shotCycle++;
    } else {
        coolDown = 0.3;
        shotCycle++;
    }
    Engine::Point diff = Engine::Point(50, -35);
    getPlayScene()->BulletGroup->AddNewObject(new BasicPea(Position + diff));
    AudioHelper::PlayAudio("throw.mp3");
}
