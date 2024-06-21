#include <allegro5/base.h>

#include "Engine/AudioHelper.hpp"
#include "Bullet/BasicPea.hpp"
#include "Engine/Group.hpp"
#include "CherryBomb.hpp"
#include "Scene/PlayScene.hpp"
#include "Zombie/Zombie.hpp"

const int CherryBomb::Price = 150;

CherryBomb::CherryBomb(float x, float y) :
        Plant("play/cherrybomb.png", x, y, INT16_MAX, Price, 0, PlantType::OTHER,"cherrybomb") {
    // Move center downward, since we the turret head is slightly biased upward.
    Anchor.y += 8.0f / GetBitmapHeight();
    reload = 1.5;
}

void CherryBomb::CreatePea() {
    AudioHelper::PlayAudio("cherrybomb.ogg");
    for (auto& it : getPlayScene()->EnemyGroup->GetObjects()) {
        Zombie* enemy = dynamic_cast<Zombie*>(it);
        if((enemy->Position - Position).Magnitude() < 225)
            enemy->TakeDamage(INT16_MAX);
    }
    getPlayScene()->lawn[pos_x][pos_y] = nullptr;
    getPlayScene()->mapState[pos_x][pos_y] = TILE_EMPTY;
    getPlayScene()->PlantGroup->RemoveObject(objectIterator);
}
