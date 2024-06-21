#include "Engine/AudioHelper.hpp"
#include "Bullet/BasicPea.hpp"
#include "Engine/Group.hpp"
#include "Shovel.hpp"
#include "Scene/PlayScene.hpp"

Shovel::Shovel(float x, float y) :
        Plant("play/shovel.png", x, y,0, 0, 0, PlantType::OTHER) {
    // Move center downward, since we the turret head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
}

void Shovel::CreatePea() {
}
