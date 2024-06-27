#include "Bombnut.hpp"
#include "Scene/PlayScene.hpp"

Bombnut::Bombnut(float x, float y) :
Plant(
    "bombnut",
    "play/bombnut.png",
    x,
    y,
    0,
    0,
    0
) {
    plantType = PlantType::OTHER;
    Anchor.y += 8.0f / GetBitmapHeight();
}

void Bombnut::CreatePea() {
}
