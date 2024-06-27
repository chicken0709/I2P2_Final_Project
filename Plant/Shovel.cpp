#include "Shovel.hpp"
#include "Scene/PlayScene.hpp"

Shovel::Shovel(float x, float y) :
Plant(
    "play/shovel.png",
    x, y,
    0,
    0,
    0,
    PlantType::OTHER,
    "shovel",
    0,
    0,
    0,
    {0}
) {
    Anchor.y += 8.0f / GetBitmapHeight();
}
