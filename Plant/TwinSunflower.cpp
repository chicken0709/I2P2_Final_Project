#include <string>

#include "Engine/AudioHelper.hpp"
#include "Bullet/BasicPea.hpp"
#include "Engine/Group.hpp"
#include "TwinSunflower.hpp"
#include "Scene/PlayScene.hpp"
#include "Sun.hpp"

const int TwinSunflower::Price = 200;

TwinSunflower::TwinSunflower(float x, float y) :
        Plant("play/twin_sunflower.png", x, y, 10, Price, 20, PlantType::SUNFLOWER,"twinsunflower",25,83,84,{25}) {
    // Move center downward, since we the turret head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
    reload = 10;
}

void TwinSunflower::CreatePea() {
    Engine::Point diff1 = Engine::Point(50, 20);
    Engine::Point diff2 = Engine::Point(25, 20);
    getPlayScene()->BulletGroup->AddNewObject(new Sun("play/sun.png", Position + diff1));
    getPlayScene()->BulletGroup->AddNewObject(new Sun("play/sun.png", Position + diff2));
}
