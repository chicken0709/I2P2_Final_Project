#include <string>

#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"

#include "GatlinPeashooter.hpp"
#include "Bullet/BasicPea.hpp"
#include "Scene/PlayScene.hpp"

const int GatlinPeashooter::Price = 450;

GatlinPeashooter::GatlinPeashooter(float x, float y) :
Plant(
    "play/gatlin_peashooter.png",
    x, y,
    10,
    Price,
    0.3,
    PlantType::PEASHOOTER,
    "gatlinpeashooter",
    13,
    88,
    84,
    {13}
) {
    Anchor.y += 8.0f / GetBitmapHeight();
}

void GatlinPeashooter::CreatePea() {
    if(shotCycle == 4) {
        coolDown = 0.3;
        shotCycle = 0;
        return;
    }
    if(shotCycle == 3) {
        coolDown = 0.6;
        shotCycle++;
    } else {
        coolDown = 0.3;
        shotCycle++;
    }
    Engine::Point diff = Engine::Point(65, -35);
    getPlayScene()->BulletGroup->AddNewObject(new BasicPea(Position + diff));
    AudioHelper::PlayAudio("throw.mp3");
}