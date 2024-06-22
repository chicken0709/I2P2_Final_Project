#include <string>

#include "Engine/AudioHelper.hpp"
#include "Bullet/BasicPea.hpp"
#include "Engine/Group.hpp"
#include "Sunflower.hpp"
#include "Scene/PlayScene.hpp"
#include "Sun.hpp"

const int Sunflower::Price = 50;

Sunflower::Sunflower(float x, float y) :
        Plant("play/sunflower.png", x, y, 10, Price, 20, PlantType::SUNFLOWER,"sunflower",25,73,74,{25}) {
    // Move center downward, since we the turret head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
    reload = 10;
}

void Sunflower::CreatePea() {
    Engine::Point normalized = Engine::Point(50, 20);
    // Change bullet position to the front of the gun barrel.
    getPlayScene()->BulletGroup->AddNewObject(new Sun("play/sun.png", Position + normalized, this));
}
