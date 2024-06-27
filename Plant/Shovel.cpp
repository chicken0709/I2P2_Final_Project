#include "Shovel.hpp"
#include "Scene/PlayScene.hpp"

Shovel::Shovel(float x, float y) :
Plant(
    "shovel",
    "play/shovel.png",
    x, y,
    0,
    0,
    0,
    PlantType::OTHER
) {
    Anchor.y += 8.0f / GetBitmapHeight();
}

void Shovel::CreatePea() {
}
