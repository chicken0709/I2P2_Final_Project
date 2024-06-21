#include "Engine/AudioHelper.hpp"
#include "Bullet/BasicPea.hpp"
#include "Engine/Group.hpp"
#include "Torchwood.hpp"
#include "Scene/PlayScene.hpp"

const int Torchwood::Price = 175;

Torchwood::Torchwood(float x, float y) :
        Plant("play/Torchwood.png", x, y, 10, Price, 0, PlantType::TORCHWOOD) {
    // Move center downward, since we the turret head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
}

void Torchwood::CreatePea() {
}
