#include <string>

#include "Engine/AudioHelper.hpp"
#include "Bullet/BasicPea.hpp"
#include "Engine/Group.hpp"
#include "TwinSunflower.hpp"
#include "Scene/PlayScene.hpp"
#include "Sun.hpp"

const int TwinSunflower::Price = 200;

TwinSunflower::TwinSunflower(float x, float y) :
        Plant("play/twin_sunflower.png", x, y, 10, Price, 20, PlantType::SUNFLOWER,"twinsunfolwer") {
    // Move center downward, since we the turret head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
    reload = 10;
}

void TwinSunflower::CreatePea() {
    Engine::Point normalized = Engine::Point(50, 20);
    Engine::Point normalized2 = Engine::Point(25, 20);
    // Change bullet position to the front of the gun barrel.
    getPlayScene()->BulletGroup->AddNewObject(new Sun("play/sun.png", Position + normalized, this));
    getPlayScene()->BulletGroup->AddNewObject(new Sun("play/sun.png", Position + normalized2, this));
}
