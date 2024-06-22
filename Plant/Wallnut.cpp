#include "Wallnut.hpp"
#include "Scene/PlayScene.hpp"

const int Wallnut::Price = 50;

Wallnut::Wallnut(float x, float y) :
        Plant("play/wallnut.png", x, y, 200, Price, 0, PlantType::OTHER,"wallnut") {
    // Move center downward, since we the turret head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
}

void Wallnut::CreatePea() {
}
