#include "Bombnut.hpp"
#include "Scene/PlayScene.hpp"

const int Bombnut::Price = 0;

Bombnut::Bombnut(float x, float y) :
Plant(
    "play/bombnut.png",
    x, y,
    0,
    Price,
    0,
    PlantType::OTHER,
    "bombnut",
    0,
    0,
    0,
    {17,17,17}
) {
    Anchor.y += 8.0f / GetBitmapHeight();
}
