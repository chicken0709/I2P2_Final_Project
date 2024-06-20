#include "Engine/AudioHelper.hpp"
#include "Bullet/BasicPea.hpp"
#include "Engine/Group.hpp"
#include "Shovel.hpp"
#include "Scene/PlayScene.hpp"

const int Shovel::Price = 0;

Shovel::Shovel(float x, float y) :
        Plant("play/shovel.png", x, y,100, 1000, Price, 1000, PlantType::PEASHOOTER) {
    // Move center downward, since we the turret head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
}

void Shovel::CreatePea() {

}
