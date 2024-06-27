#include "Engine/AudioHelper.hpp"
#include "Engine/Group.hpp"

#include "Wallnut.hpp"
#include "Scene/PlayScene.hpp"

const int Wallnut::Price = 50;

Wallnut::Wallnut(float x, float y) :
Plant(
    "play/wallnut.png",
    x, y,
    200,
    Price,
    0,
    PlantType::WALLNUT,
    "wallnut",
    51,
    65,
    73,
    {17,17,17}
) {
    Anchor.y += 8.0f / GetBitmapHeight();
}

void Wallnut::CreatePea() {
}

void Wallnut::TakeDamage(float damage, bool shovel) {
    hp -= damage;
    if (hp <= 0) {
        if(!shovel)
            AudioHelper::PlayAudio("gulp.ogg");
        getPlayScene()->plant_lawn[pos_x][pos_y] = nullptr;
        getPlayScene()->mapState[pos_x][pos_y] = TILE_EMPTY;
        getPlayScene()->PlantGroup->RemoveObject(objectIterator);
    }
    if(hp == 133) {
        animationIndex = 1;
    }
    else if(hp == 66) {
        animationIndex = 2;
    }
}
